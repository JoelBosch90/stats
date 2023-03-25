#ifndef STORE_RECORD_H
#define STORE_RECORD_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include "../read_access_record/read_access_record.h"

int store_record(std::string line, std::vector<std::string> latest_record_strings, sqlite3 *database);

#endif