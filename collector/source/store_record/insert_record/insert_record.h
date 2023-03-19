#ifndef INSERT_RECORD_H
#define INSERT_RECORD_H

#include "../../read_access_record/read_access_record.h"
#include <sqlite3.h>

int insert_record(access_record record, sqlite3 *database);

#endif