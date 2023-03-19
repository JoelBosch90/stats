#ifndef PROCESS_REVERSED_LINE_H
#define PROCESS_REVERSED_LINE_H

#include <string>
#include <functional>
#include <vector>
#include <sqlite3.h>

int process_reversed_line(std::function<int(std::string, std::vector<std::string>, sqlite3 *)> process, std::string line, std::vector<std::string>, sqlite3 *database);

#endif