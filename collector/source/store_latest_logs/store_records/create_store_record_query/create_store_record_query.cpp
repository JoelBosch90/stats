#include "create_store_record_query.h"
#include "../../join_strings/join_strings.h"
#include <vector>
using namespace std;

string create_store_record_query(string table_name)
{
  string query;
  vector<string> columns{
      "REMOTE_ADDRESS",
      "REMOTE_USER",

      "LOCAL_TIME",
      "TIMEZONE",

      "HTTP_REQUEST_METHOD",
      "HTTP_REQUEST_PATH",
      "HTTP_REQUEST_QUERY",
      "HTTP_REQUEST_FRAGMENT",
      "HTTP_REQUEST_VERSION",

      "HTTP_STATUS_CODE",

      "BYTES_SENT",

      "REFERRER_PROTOCOL",
      "REFERRER_AUTHENTICATION",
      "REFERRER_DOMAIN",
      "REFERRER_PORT",
      "REFERRER_QUERY",
      "REFERRER_FRAGMENT",

      "BROWSER_NAME",
      "BROWSER_VERSION",
      "RENDERING_ENGINE_NAME",
      "RENDERING_ENGINE_VERSION",
      "OPERATING_SYSTEM",
      "DEVICE_TYPE"};
  vector<string> placeholders(columns.size(), "?");

  query.append("INSERT INTO " + table_name + " (");
  query.append(join_strings(columns, ", "));
  query.append(") VALUES(");
  query.append(join_strings(placeholders, ", "));
  query.append(");");

  return query;
};