#include "open_database.h"

int open_database(string name, sqlite3 *database)
{
  if (sqlite3_open(name.c_str(), &database))
    return EXIT_FAILURE;

  sqlite3_stmt *statement;

  // @TODO: Set up tables, etc.
  string sql =
      "CREATE TABLE ACCESS_RECORDS("

      "ID INT PRIMARY KEY NOT NULL,"

      "FULL_RECORD TEXT,"

      "REMOTE_ADDRESS TEXT,"
      "REMOTE_USER TEXT,"

      "LOCAL_TIME TEXT,"
      "TIMEZONE TEXT,"

      "HTTP_REQUEST_METHOD TEXT,"
      "HTTP_REQUEST_PATH TEXT,"
      "HTTP_REQUEST_QUERY TEXT,"
      "HTTP_REQUEST_FRAGMENT TEXT,"
      "HTTP_REQUEST_VERSION TEXT,"

      "HTTP_STATUS_CODE INT,"

      "BYTES_SENT INT,"

      "REFERRER_PROTOCOL TEXT,"
      "REFERRER_AUTHENTICATION TEXT,"
      "REFERRER_DOMAIN TEXT,"
      "REFERRER_PORT TEXT,"
      "REFERRER_QUERY TEXT,"
      "REFERRER_FRAGMENT TEXT,"

      "BROWSER_NAME TEXT,"
      "BROWSER_VERSION TEXT,"
      "RENDERING_ENGINE_NAME TEXT,"
      "RENDERING_ENGINE_VERSION TEXT,"
      "OPERATING_SYSTEM TEXT,"
      "DEVICE_TYPE TEXT"

      ");";

  sqlite3_prepare_v2(
      database,
      sql.c_str(),
      sql.length(),
      &statement,
      nullptr);

  return EXIT_SUCCESS;
}