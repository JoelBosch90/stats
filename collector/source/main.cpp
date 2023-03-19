#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>
#include "initialize_database/initialize_database.h"
#include "read_access_record/read_access_record.h"
#include "read_lines/read_lines.h"
#include "store_record/store_record.h"

extern int EARLY_RETURN = -1;

int main()
{
  sqlite3 *database;
  std::fstream file;
  std::string database_path = "../data/stats.db";
  std::string log_path = "../../proxy/logs/access.log";

  if (sqlite3_open_v2(database_path.c_str(), &database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr))
  {
    std::cerr << "ERROR: Could not open database: " << sqlite3_errmsg(database) << std::endl;
    return EXIT_FAILURE;
  }

  if (initialize_database(database))
  {
    std::cerr << "ERROR: Could not initialize database: " << sqlite3_errmsg(database) << std::endl;
    return EXIT_FAILURE;
  }

  file.open(log_path, std::ios::in);
  if (!file.is_open())
  {
    std::cerr << "ERROR: Could not open file: " << log_path << std::endl;
    return EXIT_FAILURE;
  }

  if (read_lines(file, store_record, database) != EXIT_SUCCESS)
  {
    std::cerr << "ERROR: Error writing to database: " << sqlite3_errmsg(database) << std::endl;
    return EXIT_FAILURE;
  };

  file.close();
  sqlite3_close(database);

  return EXIT_SUCCESS;
}