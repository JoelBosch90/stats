#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>
using namespace std;

#include "open_database/open_database.h"
#include "read_access_record/read_access_record.h"
#include "read_lines/read_lines.h"

void print_access_record(string line)
{
  access_record record = read_access_record(line);

  cout << "\n";
  cout << "Remote address:\t" << record.remote_address << "\n";
  cout << "Remote user:\t" << record.remote_user << "\n";
  cout << "Local time:\t" << record.time.local_time << " " << record.time.timezone << "\n";
  cout << "Request:\t" << record.request.method + " " + record.request.path + record.request.query + record.request.fragment + " " + record.request.version << "\n";
  cout << "Status:\t\t" << record.http_status_code << "\n";
  cout << "Bytes sent:\t" << record.bytes_sent << "\n";
  // cout << "Referrer:\t" << record.referrer << "\n";
  cout << "User agent:\t" << record.user_agent << "\n";
}

int main()
{
  sqlite3 *database;
  fstream file;

  if (open_database("../data/stats.db", &database))
  {
    cerr << "ERROR: Could not open database: " << sqlite3_errmsg(database) << "\n";
    return EXIT_FAILURE;
  }

  file.open("../../proxy/logs/access.log", ios::in);

  if (!file.is_open())
  {
    cerr << "ERROR: Could not open file.\n";
    return EXIT_FAILURE;
  }

  read_lines(file, print_access_record);

  file.close();
  sqlite3_close(database);

  return EXIT_SUCCESS;
}