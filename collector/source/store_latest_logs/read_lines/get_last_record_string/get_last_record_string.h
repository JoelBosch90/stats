#ifndef GET_LAST_LOCAL_STRING_H
#define GET_LAST_LOCAL_STRING_H

#include <sqlite3.h>
#include <vector>
#include <string>

std::vector<std::string> get_last_record_string(sqlite3 *database);

#endif