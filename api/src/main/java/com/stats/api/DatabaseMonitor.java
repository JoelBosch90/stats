package com.stats.api;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.SQLException;
import javax.sql.DataSource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

@Component
public class DatabaseMonitor {
  private final MessageService messageService;
  private final DataSource dataSource;
  private int lastId = 0;

  @Autowired
  public DatabaseMonitor(MessageService messageService, DataSource dataSource) {
    this.messageService = messageService;
    this.dataSource = dataSource;
  }

  @Scheduled(fixedRate = 5000) // Check for new entries every 5 seconds
  public void checkForNewEntries() {
    try (Connection connection = dataSource.getConnection();
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement
            .executeQuery("SELECT id, data FROM my_table WHERE id > " + lastId + " ORDER BY id")) {

      while (resultSet.next()) {
        int id = resultSet.getInt("id");
        String data = resultSet.getString("data");

        messageService.sendMessageToTopic("new_entries", data);

        lastId = id;
      }
    } catch (SQLException e) {
      // Handle exception
    }
  }
}