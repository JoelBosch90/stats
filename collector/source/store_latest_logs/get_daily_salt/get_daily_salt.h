#ifndef GET_DAILY_SALT_H
#define GET_DAILY_SALT_H

#include <string>
#include <sqlite3.h>

std::string get_daily_salt(sqlite3 *database);

#endif