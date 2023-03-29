#ifndef GET_SALT_H
#define GET_SALT_H

#include <string>
#include <sqlite3.h>

std::string get_salt(std::string timestamp, sqlite3 *database);

#endif