#ifndef GET_CURRENT_SALT_H
#define GET_CURRENT_SALT_H

#include <string>
#include <sqlite3.h>

std::string get_current_salt(sqlite3 *database);

#endif