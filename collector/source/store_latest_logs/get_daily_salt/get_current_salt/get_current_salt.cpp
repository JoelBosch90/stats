#include "get_current_salt.h"
#include "../time_point_to_string/time_point_to_string.h"
#include <chrono>
using namespace std;

string get_current_salt(sqlite3 *database)
{
  sqlite3_stmt *statement;
  string query = "SELECT SALT, CREATED_AT FROM SALTS WHERE CREATED_AT == (SELECT MAX(CREATED_AT) FROM SALTS) LIMIT 1;";
  string salt = "";
  string created_at;
  string created_at_day;
  string today = time_point_to_string(chrono::system_clock::now()).substr(0, 10);

  sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr);

  if (sqlite3_step(statement) == SQLITE_ROW)
  {
    created_at = reinterpret_cast<const char *>(sqlite3_column_text(statement, 1));
    created_at_day = created_at.substr(0, 10);

    if (created_at == today)
    {
      salt = reinterpret_cast<const char *>(sqlite3_column_text(statement, 0));
    }
  }

  sqlite3_finalize(statement);

  return salt;
}