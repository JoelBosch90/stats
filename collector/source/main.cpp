#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>

#include "database_open/database_open.h"
#include "read_access_record/read_access_record.h"
#include "read_lines/read_lines.h"

void print_access_record(std::string line)
{
  access_record record = read_access_record(line);

  std::cout << "\n";
  std::cout << line << "\n";
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
  std::cout << "Referrer:\t\t" << record.referrer.protocol << "://" << record.referrer.authentication << record.referrer.domain << ":" << record.referrer.port << "\n";
  std::cout << "Browser:\t\t" << record.user_agent.browser_name << "/" << record.user_agent.browser_version << "\n";
  std::cout << "Rendering engine:\t" << record.user_agent.rendering_engine_name << "/" << record.user_agent.rendering_engine_version << "\n";
  std::cout << "Operating system:\t" << record.user_agent.operating_system << " on " + record.user_agent.device_type + "\n";
}

int main()
{
  sqlite3 *database;
  std::fstream file;
  std::string database_path = "../data/stats.db";
  std::string log_path = "../../proxy/logs/access.log";

  if (database_open(database_path, database))
  {
    cerr << "ERROR: Could not open database: " << sqlite3_errmsg(database) << "\n";
    return EXIT_FAILURE;
  }

  file.open(log_path, ios::in);

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