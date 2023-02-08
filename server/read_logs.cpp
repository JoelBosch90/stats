#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>
using namespace std;

#include <read_logs/open_database.h>
#include <read_logs/string_to_access_record.h>
#include <read_logs/read_lines_from_stream_from_end.h>

void print_access_record(string line)
{
  default_access_record record = string_to_access_record(line);

  cout << "\n";
  cout << "Remote address:\t" << record.remote_address << "\n";
  cout << "Remote user:\t" << record.remote_user << "\n";
  cout << "Local time:\t" << record.local_time << "\n";
  cout << "Request:\t" << record.request << "\n";
  cout << "Status:\t\t" << record.status << "\n";
  cout << "Bytes sent:\t" << record.bytes_sent << "\n";
  cout << "Referrer:\t" << record.referrer << "\n";
  cout << "User agent:\t" << record.user_agent << "\n";
}

int main()
{
  sqlite3 *database;
  fstream file;

  if (open_database("files/stats.db", &database))
  {
    cerr << "ERROR: Could not open database: " << sqlite3_errmsg(database) << "\n";
    return EXIT_FAILURE;
  }

  file.open("./../proxy/logs/access.log", ios::in);

  if (!file.is_open())
  {
    cerr << "ERROR: Could not open file.\n";
    return EXIT_FAILURE;
  }

  read_lines_from_stream_from_end(file, print_access_record);

  file.close();
  sqlite3_close(database);

  return EXIT_SUCCESS;
}