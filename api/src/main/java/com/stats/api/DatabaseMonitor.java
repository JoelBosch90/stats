package com.stats.api;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.concurrent.atomic.AtomicLong;
import java.util.logging.Logger;
import java.sql.SQLException;
import javax.sql.DataSource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
public class DatabaseMonitor {
  private static final Logger LOGGER = Logger.getLogger(DatabaseMonitor.class.getName());
  private final MessageService messageService;
  private final DataSource dataSource;
  private AtomicLong lastProcessedId = new AtomicLong(0);

  @Autowired
  public DatabaseMonitor(MessageService messageService, DataSource dataSource) {
    this.messageService = messageService;
    this.dataSource = dataSource;
  }

  private String getNewAccessRecordsQuery(int lastProcessedId) {
    String id_column = AccessRecord.ID_COLUMN;
    String columns = String.join(", ", AccessRecord.COLUMNS);

    return "SELECT " + columns
        + " FROM " + AccessRecord.TABLE_NAME
        + " WHERE " + id_column + " > " + lastProcessedId
        + " ORDER BY " + id_column + " ASC";
  }

  private void processNewAccessRecord(ResultSet resultSet) {
    AccessRecord record = new AccessRecord(resultSet);

    messageService.sendMessageToTopic("new_record", record.toJSON());
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

  @Scheduled(fixedRateString = "${UPDATE_INTERVAL:60000}")
  public void checkForNewAccessRecords() {
    LOGGER.info("DATABASE_MONITOR: Checking for new access records...");
    String query = getNewAccessRecordsQuery(lastProcessedId.intValue());
    try (
        Connection connection = dataSource.getConnection();
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(query)) {
      processNewAccessRecords(resultSet);
    } catch (SQLException error) {
      LOGGER.severe("DATABASE_MONITOR: An error occurred while checking for new access records: " + error.getMessage());
    }
  }
}