#include "get_dated_salt.h"
#include <chrono>
using namespace std;

string get_dated_salt(string timestamp, sqlite3 *database)
{
  sqlite3_stmt *statement;
  string query = "SELECT SALT FROM SALTS WHERE DATE = ? LIMIT 1;";
  string salt = "";
  string date = timestamp.substr(0, 10);

  sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr);
  sqlite3_bind_text(statement, 1, date.c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(statement) == SQLITE_ROW)
    salt = reinterpret_cast<const char *>(sqlite3_column_text(statement, 0));

  sqlite3_finalize(statement);

  return salt;
}