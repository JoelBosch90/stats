#ifndef INSERT_NEW_SALT_H
#define INSERT_NEW_SALT_H

#include <string>
#include <sqlite3.h>

int insert_new_salt(std::string salt, std::string timestamp, sqlite3 *database);

#endif