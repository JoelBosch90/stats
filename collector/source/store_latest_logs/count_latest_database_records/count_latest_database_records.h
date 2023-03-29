#ifndef COUNT_LATEST_DATABASE_RECORDS_H
#define COUNT_LATEST_DATABASE_RECORDS_H

#include <string>
#include <sqlite3.h>

int count_latest_database_records(std::string earliest, sqlite3 *database);

#endif