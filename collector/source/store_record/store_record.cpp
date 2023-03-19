#include "store_record.h"
#include "../insert_row/insert_row.h"
#include <vector>
using namespace std;

int store_record(access_record record, sqlite3 *database)
{
  vector<string> columns{
      "FULL_RECORD",

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

  vector<string> values{
      record.full_text,

      record.remote_address,
      record.remote_user,

      record.time.local_time,
      record.time.timezone,

      record.request.method,
      record.request.path,
      record.request.query,
      record.request.fragment,
      record.request.version,

      to_string(record.http_status_code),

      to_string(record.bytes_sent),

      record.referrer.protocol,
      record.referrer.authentication,
      record.referrer.domain,
      record.referrer.port,
      record.referrer.query,
      record.referrer.fragment,

      record.user_agent.browser_name,
      record.user_agent.browser_version,
      record.user_agent.rendering_engine_name,
      record.user_agent.rendering_engine_version,
      record.user_agent.operating_system,
      record.user_agent.device_type};

  return insert_row("ACCESS_RECORDS", columns, values, database);
};