#include "get_last_record_time.h"
using namespace std;

string get_last_record_time(sqlite3 *database)
{
  sqlite3_stmt *statement;
  string query = "SELECT LOCAL_TIME FROM ACCESS_RECORDS WHERE LOCAL_TIME == (SELECT MAX(LOCAL_TIME) FROM ACCESS_RECORDS) LIMIT 1;";
  string result;

  sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr);

  if (sqlite3_step(statement) == SQLITE_ROW)
    result = reinterpret_cast<const char *>(sqlite3_column_text(statement, 0));

  sqlite3_finalize(statement);

  return result;
};