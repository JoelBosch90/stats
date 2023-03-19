#include "insert_row.h"
#include "../join_strings/join_strings.h"
using namespace std;

string create_empty_row_query(string table, vector<string> columns)
{
  string query;
  vector<string> placeholders(columns.size(), "?");

  query.append("INSERT INTO " + table + " (");
  query.append(join_strings(columns, ", "));
  query.append(") VALUES(");
  query.append(join_strings(placeholders, ", "));
  query.append(");");

  return query;
}

int insert_row(string table, vector<string> columns, vector<string> values, sqlite3 *database)
{
  sqlite3_stmt *statement;
  string query = create_empty_row_query(table, columns);

  if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr) != SQLITE_OK)
    return EXIT_FAILURE;

  for (int index = 0; index < values.size(); ++index)
    sqlite3_bind_text(statement, index + 1, values[index].c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(statement) != SQLITE_DONE)
    return EXIT_FAILURE;

  sqlite3_finalize(statement);

  return EXIT_SUCCESS;
};