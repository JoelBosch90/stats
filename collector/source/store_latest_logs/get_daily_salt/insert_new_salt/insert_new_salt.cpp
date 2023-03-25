#include "insert_new_salt.h"
#include "remove_all_salts/remove_all_salts.h"
#include "../../insert_row/insert_row.h"
#include "../time_point_to_string/time_point_to_string.h"
#include <chrono>
using namespace std;

int insert_new_salt(string salt, sqlite3 *database)
{
  remove_all_salts(database);
  string now = time_point_to_string(chrono::system_clock::now());
  vector<string> columns = {"SALT", "CREATED_AT"};
  vector<string> values = {salt, now};

  return insert_row("SALTS", columns, values, database);
}