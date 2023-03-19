#ifndef DATABASE_INSERT_H
#define DATABASE_INSERT_H

#include <sqlite3.h>
#include <string>
using namespace std;

int database_insert(string name, sqlite3 *database);

#endif