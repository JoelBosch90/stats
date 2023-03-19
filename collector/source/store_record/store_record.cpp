#include "store_record.h"
#include "../read_access_record/read_access_record.h"
#include "insert_record/insert_record.h"
#include "record_in_list/record_in_list.h"
#include <vector>
using namespace std;

extern const int EARLY_RETURN;

int store_record(string line, vector<string> latest_record_strings, sqlite3 *database)
{
  access_record record = read_access_record(line);
  vector<access_record> latest_records;

  for (string record_string : latest_record_strings)
    latest_records.push_back(read_access_record(record_string));

  string latest_time = latest_records.size() > 0 ? latest_records[0].time.local_time : "1970-01-0 00:00:00";

  if (latest_records.size() == 0)
    return insert_record(record, database);

  if (record.time.local_time < latest_time)
    return EARLY_RETURN;

  if (record.time.local_time == latest_time && (record_in_list(record, latest_records)))
    return EARLY_RETURN;

  return insert_record(record, database);
};