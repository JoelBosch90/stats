#ifndef READ_LINES_H
#define READ_LINES_H

#include <istream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "../read_access_record/read_access_record.h"

std::vector<access_record> read_lines(std::istream &input, std::string until, sqlite3 *database);

#endif