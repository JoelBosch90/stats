#include "open_database.h"

int open_database(string name, sqlite3 **database)
{
  if (sqlite3_open(name.c_str(), database))
    return EXIT_FAILURE;

  // @TODO: Set up tables, etc.

  return EXIT_SUCCESS;
}