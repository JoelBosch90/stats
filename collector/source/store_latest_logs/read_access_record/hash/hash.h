#ifndef HASH_H
#define HASH_H

#include <string>
#include <sqlite3.h>

std::string hash(std::string to_hash, std::string timestamp, sqlite3 *database);

#endif