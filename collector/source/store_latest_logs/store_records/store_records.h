#ifndef STORE_RECORDS_H
#define STORE_RECORDS_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include "../read_access_record/read_access_record.h"

int store_records(std::vector<access_record> records, sqlite3 *database);

#endif