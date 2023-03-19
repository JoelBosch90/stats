#ifndef INSERT_ROW_H
#define INSERT_ROW_H

#include <string>
#include <vector>
#include <sqlite3.h>

int insert_row(std::string name, std::vector<std::string> columns, std::vector<std::string> values, sqlite3 *database);

#endif