#ifndef CREATE_TABLE_H
#define CREATE_TABLE_H

#include <string>
#include <vector>
#include <sqlite3.h>

int create_table(std::string name, std::vector<std::string> *rows, sqlite3 *database);

#endif