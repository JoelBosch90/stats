#ifndef SETUP_DATABASE_H
#define SETUP_DATABASE_H

#include <sqlite3.h>
#include <string>
using namespace std;

int open_database(string name, sqlite3 **database);

#endif