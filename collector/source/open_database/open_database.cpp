#include "open_database.h"

int open_database(string name, sqlite3 **database)
{
  if (sqlite3_open(name.c_str(), database))
    return EXIT_FAILURE;

  // @TODO: Set up tables, etc.
  string sql =
      "CREATE TABLE ACCESS_RECORDS("
      "ID INT PRIMARY KEY NOT NULL,"

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
      "REFERRER_DOMAIN TEXT,"
      "REFERRER_PORT TEXT,"

      "USER_AGENT TEXT,";

  return EXIT_SUCCESS;
}