#ifndef GET_LAST_RECORD_TIME_H
#define GET_LAST_RECORD_TIME_H

#include <sqlite3.h>
#include <string>

std::string get_last_record_time(sqlite3 *database);

#endif