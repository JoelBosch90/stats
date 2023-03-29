#ifndef GET_DATED_SALT_H
#define GET_DATED_SALT_H

#include <string>
#include <sqlite3.h>

std::string get_dated_salt(std::string timestamp, sqlite3 *database);

#endif