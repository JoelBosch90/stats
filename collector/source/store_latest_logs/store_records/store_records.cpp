#include "store_records.h"
#include "../read_access_record/read_access_record.h"
#include "create_store_record_query/create_store_record_query.h"
#include "bind_record_to_statement/bind_record_to_statement.h"
#include <vector>
using namespace std;

int store_records(vector<access_record> records, sqlite3 *database)
{
  sqlite3_stmt *statement;
  string query = create_store_record_query("ACCESS_RECORDS");
  int exit_code = EXIT_SUCCESS;

  if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, nullptr) != SQLITE_OK)
    exit_code = EXIT_FAILURE;

  for (const access_record record : records)
  {
    if (exit_code != EXIT_FAILURE)
      exit_code = bind_record_to_statement(record, statement) == EXIT_FAILURE;
  }

  if (sqlite3_finalize(statement) != SQLITE_OK)
    exit_code = EXIT_FAILURE;

  return exit_code;
};