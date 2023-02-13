#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>
using namespace std;

#include "open_database/open_database.h"
#include "read_line/read_line.h"
#include "read_lines/read_lines.h"

void print_access_record(string line)
{
  default_access_record record = read_line(line);

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

  if (open_database("../data/stats.db", &database))
  {
    cerr << "ERROR: Could not open database: " << sqlite3_errmsg(database) << "\n";
    return EXIT_FAILURE;
  }

  file.open("./../../proxy/logs/access.log", ios::in);

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