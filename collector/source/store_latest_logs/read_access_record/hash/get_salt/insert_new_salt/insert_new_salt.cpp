#include "insert_new_salt.h"
#include "../../../../insert_row/insert_row.h"
#include "../../../../time_point_to_string/time_point_to_string.h"
#include <chrono>
using namespace std;

int insert_new_salt(string salt, string timestamp, sqlite3 *database)
{
  string now = time_point_to_string(chrono::system_clock::now());
  string date = timestamp.substr(0, 10);
  vector<string> columns = {"SALT", "DATE", "CREATED_AT"};
  vector<string> values = {salt, date, now};

  return insert_row("SALTS", columns, values, database);
}