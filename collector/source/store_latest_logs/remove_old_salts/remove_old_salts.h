#ifndef REMOVE_OLD_SALTS_H
#define REMOVE_OLD_SALTS_H

#include <sqlite3.h>

int remove_old_salts(sqlite3 *database);

#endif