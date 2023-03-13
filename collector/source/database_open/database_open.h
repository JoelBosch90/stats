#ifndef DATABASE_OPEN_H
#define DATABASE_OPEN_H

#include <sqlite3.h>
#include <string>
using namespace std;

int database_open(string name, sqlite3 *database);

#endif