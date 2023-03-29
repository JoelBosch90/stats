#ifndef BIND_RECORD_TO_STATEMENT_H
#define BIND_RECORD_TO_STATEMENT_H

#include "../../read_access_record/read_access_record.h"
#include <sqlite3.h>

int bind_record_to_statement(access_record record, sqlite3_stmt *statement);

#endif