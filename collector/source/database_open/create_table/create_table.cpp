#include "create_table.h"

string create_table_query(string name, vector<string> *rows)
{
  string query;

  query.append("CREATE TABLE IF NOT EXISTS " + name + " (");
  query.append(join_strings(rows, ", "));
  query.append(");");

  return query;
}

int create_table_callback(void *not_used, int number_of_columns, char **column_texts, char **column_names)
{
  return EXIT_SUCCESS;
};

int create_table(string name, vector<string> *rows, sqlite3 *database)
{
  sqlite3_stmt *statement;
  string query = create_table_query(name, rows);
  char *error_message;

  sqlite3_exec(database, query.c_str(), create_table_callback, 0, &error_message);

  return EXIT_SUCCESS;
};
