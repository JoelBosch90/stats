#include "remove_old_salts.h"
#include "../time_point_to_string/time_point_to_string.h"
#include "../subtract_day_from_string/subtract_day_from_string.h"
#include <chrono>
#include <string>
using namespace std;

int remove_old_salts(sqlite3 *database)
{
  int exit_code = EXIT_SUCCESS;
  sqlite3_stmt *statement;

  // Remove all but today's and yesterday's salts.
  string query = "DELETE FROM SALTS WHERE DATE < ?;";

  // Calculate yesterday's date.
  string now = time_point_to_string(chrono::system_clock::now());
  string yesterday = subtract_day_from_string(now).substr(0, 10);

  if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr) != SQLITE_OK)
    exit_code = EXIT_FAILURE;

  if (sqlite3_bind_text(statement, 1, yesterday.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK)
    exit_code = EXIT_FAILURE;

  if (sqlite3_step(statement) != SQLITE_DONE)
    exit_code = EXIT_FAILURE;

  if (sqlite3_finalize(statement) != SQLITE_OK)
    exit_code = EXIT_FAILURE;

  return exit_code;
};