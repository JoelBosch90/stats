#include "bind_record_to_statement.h"
#include <vector>
using namespace std;

int bind_record_to_statement(access_record record, sqlite3_stmt *statement)
{
  int exit_code = EXIT_SUCCESS;

  vector<string> values{
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

  for (int index = 0; index < values.size(); index++)
    sqlite3_bind_text(statement, index + 1, values[index].c_str(), -1, SQLITE_TRANSIENT);

  // Execute the statement to add the row.
  if (sqlite3_step(statement) != SQLITE_DONE)
    exit_code = EXIT_FAILURE;

  // Prepare the statement for the next row.
  if (sqlite3_reset(statement) != SQLITE_OK)
    exit_code = EXIT_FAILURE;

  return exit_code;
};