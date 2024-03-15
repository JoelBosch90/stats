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
  private final MessageService messageService;
  private final DataSource dataSource;
  private AtomicLong lastProcessedId = new AtomicLong(0);

  // We'll try to get the update interval from the environment variables, but
  // if we cannot, we'll default to 60000 milliseconds (1 minute).
  @Value(FIXED_RATE)
  private String updateInterval;

  @Autowired
  public DatabaseMonitor(MessageService messageService, DataSource dataSource) {
    this.messageService = messageService;
    this.dataSource = dataSource;
  }

  private String getNewAccessRecordsQuery(int lastProcessedId) {
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
        + " AND " + id + " > " + lastProcessedId
        + " ORDER BY " + local_time + " ASC";
  }

  private void processNewAccessRecord(ResultSet resultSet) {
    AccessRecord record = new AccessRecord(resultSet);

    LOGGER.info("DATABASE_MONITOR: Processing new access record: " + record.toJSON());
    messageService.sendMessageToTopic("new_record", "test message");
    lastProcessedId = new AtomicLong(record.getId());
  }

  private void processNewAccessRecords(ResultSet resultSet) throws SQLException {
    if (resultSet == null) {
      return;
    }

    while (resultSet.next()) {
      processNewAccessRecord(resultSet);
    }
  }

  @Scheduled(fixedRateString = FIXED_RATE)
  public void checkForNewAccessRecords() {
    LOGGER.info("DATABASE_MONITOR: Checking for new access records...");
    String query = getNewAccessRecordsQuery(lastProcessedId.intValue());
    try (
        Connection connection = dataSource.getConnection();
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(query)) {
      processNewAccessRecords(resultSet);
      LOGGER.info("DATABASE_MONITOR: Finished processing new access records...");
    } catch (SQLException error) {
      LOGGER.severe("DATABASE_MONITOR: An error occurred while checking for new access records: " + error.getMessage());
    }
  }
}