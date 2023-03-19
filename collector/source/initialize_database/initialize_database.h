#ifndef INITIALIZE_DATABASE_H
#define INITIALIZE_DATABASE_H

#include <string>
#include <sqlite3.h>

int initialize_database(sqlite3 *database);

#endif