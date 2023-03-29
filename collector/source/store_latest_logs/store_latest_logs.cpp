#include "store_latest_logs.h"
#include "initialize_database/initialize_database.h"
#include "read_lines/read_lines.h"
#include "store_records/store_records.h"
#include "get_last_record_time/get_last_record_time.h"
#include "subtract_day_from_string/subtract_day_from_string.h"
#include "get_daily_salt/get_daily_salt.h"
#include "read_access_record/read_access_record.h"
#include "count_latest_database_records/count_latest_database_records.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sqlite3.h>
using namespace std;

int store_latest_logs(string log_file_path, string database_path)
{
  int lines_read = 0;
  sqlite3 *database;
  fstream file;

  if (sqlite3_open_v2(database_path.c_str(), &database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr))
  {
    cerr << "ERROR: Could not open database: " << sqlite3_errmsg(database) << endl;
    return lines_read;
  }

  if (initialize_database(database))
  {
    cerr << "ERROR: Could not initialize database: " << sqlite3_errmsg(database) << endl;
    return lines_read;
  }

  file.open(log_file_path, ios::in);
  if (!file.is_open())
  {
    cerr << "ERROR: Could not open file: " << log_file_path << endl;
    return lines_read;
  }

  // We want to start reading logs until we get to the timestamp of the latest
  // record.
  string last_record_time_stamp = get_last_record_time(database);

  // However, it is kind of tricky to account for timezones with this. To avoid
  // all timezone trouble, we can simply look up all records up to 1 day older
  // than the latest record.
  string last_record_time_stamp_minus_day = subtract_day_from_string(last_record_time_stamp);

  // Get the daily salt value to use for hashing while processing log records.
  string salt = get_daily_salt(database);

  // Read all of the access log records that are added after this date.
  vector<access_record> log_records = read_lines(file, last_record_time_stamp_minus_day, salt);

  // Get the number of records from the database that are added after this date.
  int database_record_count = count_latest_database_records(last_record_time_stamp_minus_day, database);

  // The number of records that already exist in the database from the same
  // timeframe are overlap. Thus, we can remove those to get the new records.
  vector<access_record> new_records(log_records.begin() + database_record_count, log_records.end());

  if (store_records(new_records, database) == EXIT_SUCCESS)
    lines_read = new_records.size();

  file.close();
  sqlite3_close(database);

  return lines_read;
};