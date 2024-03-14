package com.stats.api;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.List;
import java.util.logging.Logger;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import org.springframework.lang.NonNull;
import com.fasterxml.jackson.databind.ObjectMapper;

public class AccessRecord {
  private static final Logger LOGGER = Logger.getLogger(DatabaseMonitor.class.getName());
  public static final String TABLE_NAME = "ACCESS_RECORDS";

  public static final String ID_COLUMN = "ID";
  public static final String REMOTE_USER_COLUMN = "REMOTE_USER";
  public static final String REMOTE_ADDRESS_COLUMN = "REMOTE_ADDRESS";
  public static final String LOCAL_TIME_COLUMN = "LOCAL_TIME";

  private static final List<String> INT_COLUMNS = List.of(ID_COLUMN);
  private static final List<String> STRING_COLUMNS = List.of(REMOTE_USER_COLUMN, REMOTE_ADDRESS_COLUMN,
      LOCAL_TIME_COLUMN);
  public static final List<String> COLUMNS = Stream.concat(INT_COLUMNS.stream(), STRING_COLUMNS.stream())
      .collect(Collectors.toList());

  public HashMap<String, Object> properties = new HashMap<>();

  public AccessRecord(ResultSet resultSet) {
    for (String int_column : INT_COLUMNS) {
      properties.put(int_column.toLowerCase(), getIntResult(resultSet, int_column));
    }
    for (String string_column : STRING_COLUMNS) {
      properties.put(string_column.toLowerCase(), getStringResult(resultSet, string_column));
    }
  }

  private Integer getIntResult(ResultSet resultSet, String columnName) {
    try {
      return resultSet.getInt(columnName);
    } catch (SQLException exception) {
      LOGGER.warning("Failed to get int result for column: " + columnName + " - " + exception.getMessage());
      return null;
    }
  }

  private String getStringResult(ResultSet resultSet, String columnName) {
    try {
      return resultSet.getString(columnName);
    } catch (SQLException exception) {
      LOGGER.warning("Failed to get string result for column: " + columnName + " - " + exception.getMessage());
      return null;
    }
  }

  public Integer getId() {
    Object id = properties.get(ID_COLUMN.toLowerCase());

    return id == null ? null : (Integer) id;
  }

  @NonNull
  public String toJSON() {
    ObjectMapper mapper = new ObjectMapper();
    String emptyJson = "{}";

    try {
      String json = mapper.valueToTree(properties).toString();
      return json != null ? json : emptyJson;
    } catch (Exception exception) {
      return emptyJson;
    }
  }
}
