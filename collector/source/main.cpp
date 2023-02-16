#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>

#include "open_database/open_database.h"
#include "read_access_record/read_access_record.h"
#include "read_lines/read_lines.h"

void print_access_record(std::string line)
{
  access_record record = read_access_record(line);

  std::cout << "\n";
  std::cout << line << "\n";
  std::cout << "\n";
  std::cout << "Remote address:\t\t" << record.remote_address << "\n";
  std::cout << "Remote user:\t\t" << record.remote_user << "\n";
  std::cout << "Local time:\t\t" << record.time.local_time << " " << record.time.timezone << "\n";
  std::cout << "Request method:\t\t" << record.request.method << "\n";
  std::cout << "Request path:\t\t" << record.request.path << "\n";
  std::cout << "Request query:\t\t" << record.request.query << "\n";
  std::cout << "Request fragment:\t" << record.request.fragment << "\n";
  std::cout << "Request version:\t" << record.request.version << "\n";
  std::cout << "Request status:\t\t" << record.http_status_code << "\n";
  std::cout << "Bytes sent:\t\t" << record.bytes_sent << "\n";
  std::cout << "Referrer:\t\t" << record.referrer << "\n";
  std::cout << "User agent:\t\t" << record.user_agent << "\n";
}

int main()
{
  sqlite3 *database;
  std::fstream file;

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