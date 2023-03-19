#include "create_table.h"
#include "../join_strings/join_strings.h"
using namespace std;

string create_table_query(string name, vector<string> *rows)
{
  string query;

  query.append("CREATE TABLE IF NOT EXISTS " + name + " (");
  query.append(join_strings(*rows, ", "));
  query.append(");");

  return query;
}

int create_table(string name, vector<string> *rows, sqlite3 *database)
{
  sqlite3_stmt *statement;
  string query = create_table_query(name, rows);
  int exit_code = EXIT_SUCCESS;

  if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr) != SQLITE_OK)
    exit_code = EXIT_FAILURE;

  if (sqlite3_step(statement) != SQLITE_OK)
    exit_code = EXIT_FAILURE;

  sqlite3_finalize(statement);

  return exit_code;
};
