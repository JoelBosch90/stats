#ifndef READ_LINES_H
#define READ_LINES_H

#include <istream>
#include <functional>
#include <string>
#include <sqlite3.h>

int read_lines(std::istream &input, std::function<int(std::string, sqlite3 *)> process, sqlite3 *database);

#endif