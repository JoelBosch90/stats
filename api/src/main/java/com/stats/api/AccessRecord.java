package com.stats.api;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.logging.Logger;
import org.springframework.lang.NonNull;
import org.apache.commons.codec.digest.DigestUtils;
import com.fasterxml.jackson.databind.ObjectMapper;

public class AccessRecord {
  private static final Logger LOGGER = Logger.getLogger(AccessRecord.class.getName());
  public static final String TABLE_NAME = "ACCESS_RECORDS";

  public static final String ID_COLUMN = "ID";
  public static final String REMOTE_USER_COLUMN = "REMOTE_USER";
  public static final String REMOTE_ADDRESS_COLUMN = "REMOTE_ADDRESS";
  public static final String LOCAL_TIME_COLUMN = "LOCAL_TIME";

  private static final List<String> INT_COLUMNS = List.of(ID_COLUMN);
  private static final List<String> HASH_COLUMNS = List.of(REMOTE_USER_COLUMN);
  private static final List<String> STRING_COLUMNS = List.of(REMOTE_ADDRESS_COLUMN,
      LOCAL_TIME_COLUMN);
  public static final List<String> COLUMNS = Stream
      .concat(Stream.concat(INT_COLUMNS.stream(), STRING_COLUMNS.stream()), HASH_COLUMNS.stream())
      .collect(Collectors.toList());

  public HashMap<String, Object> properties = new HashMap<>();

  public AccessRecord(ResultSet resultSet) {
    for (String intColumn : INT_COLUMNS) {
      setInt(intColumn, resultSet);
    }
    for (String hashColumn : HASH_COLUMNS) {
      setHash(hashColumn, resultSet);
    }
    for (String stringColumn : STRING_COLUMNS) {
      setString(stringColumn, resultSet);
    }
  }

  private void setInt(String columnName, ResultSet resultSet) {
    Integer result = null;
    try {
      result = resultSet.getInt(columnName);
    } catch (SQLException exception) {
      LOGGER.warning(columnName + " is not an integer.");
    }

    properties.put(columnName.toLowerCase(), result);
  }

  private void setHash(String columnName, ResultSet resultSet) {
    String result = null;
    try {
      result = resultSet.getString(columnName);
      if (result != null) {
        result = DigestUtils.sha256Hex(result);
      }
    } catch (SQLException exception) {
      LOGGER.warning(columnName + " is not a string.");
    }

    properties.put(columnName.toLowerCase(), result);
  }

  private void setString(String columnName, ResultSet resultSet) {
    String result = null;
    try {
      result = resultSet.getString(columnName);
    } catch (SQLException exception) {
      LOGGER.warning(columnName + " is not a string.");
    }

    properties.put(columnName.toLowerCase(), result);
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
      LOGGER.warning("AccessRow could not be converted to JSON.");
      return emptyJson;
    }
  }
}
