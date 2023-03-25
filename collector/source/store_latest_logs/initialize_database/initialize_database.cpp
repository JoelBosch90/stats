#include "initialize_database.h"
#include "../create_table/create_table.h"
using namespace std;

int initialize_database(sqlite3 *database)
{
  vector<string> access_records{
      "ID INTEGER PRIMARY KEY",
      "FULL_RECORD TEXT",

      "REMOTE_ADDRESS TEXT",
      "REMOTE_USER TEXT",

      "LOCAL_TIME TEXT",
      "TIMEZONE TEXT",

      "HTTP_REQUEST_METHOD TEXT",
      "HTTP_REQUEST_PATH TEXT",
      "HTTP_REQUEST_QUERY TEXT",
      "HTTP_REQUEST_FRAGMENT TEXT",
      "HTTP_REQUEST_VERSION TEXT",

      "HTTP_STATUS_CODE TEXT",

      "BYTES_SENT TEXT",

      "REFERRER_PROTOCOL TEXT",
      "REFERRER_AUTHENTICATION TEXT",
      "REFERRER_DOMAIN TEXT",
      "REFERRER_PORT TEXT",
      "REFERRER_QUERY TEXT",
      "REFERRER_FRAGMENT TEXT",

      "BROWSER_NAME TEXT",
      "BROWSER_VERSION TEXT",
      "RENDERING_ENGINE_NAME TEXT",
      "RENDERING_ENGINE_VERSION TEXT",
      "OPERATING_SYSTEM TEXT",
      "DEVICE_TYPE TEXT"};
  create_table("ACCESS_RECORDS", &access_records, database);

  vector<string> salts{
      "ID INTEGER PRIMARY KEY",
      "SALT TEXT",
      "CREATED_AT TEXT"};
  create_table("SALTS", &salts, database);

  return EXIT_SUCCESS;
}