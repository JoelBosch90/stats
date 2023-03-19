#ifndef STORE_RECORD_H
#define STORE_RECORD_H

#include <sqlite3.h>
#include "../read_access_record/read_access_record.h"

int store_record(access_record record, sqlite3 *database);

#endif