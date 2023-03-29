#include "count_latest_database_records.h"
#include <iostream>
using namespace std;

int count_latest_database_records(std::string earliest, sqlite3 *database)
{
  int count = 0;
  sqlite3_stmt *statement;
  string query = "SELECT COUNT(ID) FROM ACCESS_RECORDS WHERE LOCAL_TIME >= ?;";

  if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr) != SQLITE_OK)
  {
    cout << "ERROR: could not query database." << endl;
    return count;
  }

  sqlite3_bind_text(statement, 1, earliest.c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(statement) == SQLITE_ROW)
    count = sqlite3_column_int(statement, 0);

  sqlite3_finalize(statement);

  return count;
};