package com.stats.api;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.concurrent.atomic.AtomicLong;
import java.util.logging.Logger;
import java.sql.SQLException;
import javax.sql.DataSource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
public class DatabaseMonitor {
  private static final Logger LOGGER = Logger.getLogger(DatabaseMonitor.class.getName());
  private static final int INTERVAL_MARGIN_SECONDS = 3;
  private static final String FIXED_RATE = "${UPDATE_INTERVAL:60000}";
  private final MessageHandler messageHandler;
  private final DataSource dataSource;
  private AtomicLong lastProcessedId = new AtomicLong(0);

  // We'll try to get the update interval from the environment variables, but
  // if we cannot, we'll default to 60000 milliseconds (1 minute).
  @Value(FIXED_RATE)
  private String updateInterval;

  @Autowired
  public DatabaseMonitor(MessageHandler messageHandler, DataSource dataSource) {
    this.messageHandler = messageHandler;
    this.dataSource = dataSource;
  }

  private String getNewAccessRecordsQuery(int lastIdToSkip) {
    String local_time = AccessRecord.LOCAL_TIME_COLUMN;
    String id = AccessRecord.ID_COLUMN;

    // We want to look back a little further than our update interval to ensure
    // we don't miss any records.
    String updateIntervalInSeconds = String
        .valueOf((Integer.parseInt(updateInterval) / 1000) + INTERVAL_MARGIN_SECONDS);
    String minute_ago = "datetime('now', '-" + updateIntervalInSeconds + " seconds')";
    String columns = String.join(", ", AccessRecord.COLUMNS);

    return "SELECT " + columns
        + " FROM " + AccessRecord.TABLE_NAME
        + " WHERE " + local_time + " >= " + minute_ago
        + " AND " + id + " > " + lastIdToSkip
        + " ORDER BY " + local_time + " ASC";
  }

  private Integer processNewAccessRecord(ResultSet resultSet) {
    AccessRecord record = new AccessRecord(resultSet);

    try {
      messageHandler.broadcastMessage(record.toJSON());
    } catch (Exception error) {
      LOGGER.severe("An error occurred while broadcasting the message: " + error.getMessage());
    }

    return record.getId();
  }

  private Integer processNewAccessRecords(ResultSet resultSet) throws SQLException {
    Integer highestId = null;

    if (resultSet == null) {
      return null;
    }

    while (resultSet.next()) {
      Integer processedId = processNewAccessRecord(resultSet);

      if (processedId == null || (highestId != null && processedId > highestId)) {
        highestId = processedId;
      }
    }

    return highestId;
  }

  // This is a threadsafe method to update the last processed ID.
  private void updateLastProcessedId(Integer lastId) {
    if (lastId == null) {
      return;
    }

    long lastIdLong = lastId.longValue();

    while (true) {
      long currentLastProcessedId = lastProcessedId.get();

      if (lastIdLong <= currentLastProcessedId || lastProcessedId.compareAndSet(currentLastProcessedId, lastIdLong)) {
        break;
      }
    }
  }

  @Scheduled(fixedRateString = FIXED_RATE)
  public void checkForNewAccessRecords() {
    String query = getNewAccessRecordsQuery(lastProcessedId.intValue());

    try (
        Connection connection = dataSource.getConnection();
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(query)) {
      Integer lastId = processNewAccessRecords(resultSet);

      // We need to be threadsafe in updating the last processed ID because this
      // method is called by a scheduled task.
      updateLastProcessedId(lastId);
    } catch (SQLException error) {
      LOGGER.severe("An error occurred while checking for new access records: " + error.getMessage());
    }
  }
}