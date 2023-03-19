#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>
#include "initialize_database/initialize_database.h"
#include "read_access_record/read_access_record.h"
#include "read_lines/read_lines.h"
#include "store_record/store_record.h"

int store_access_record(std::string line, sqlite3 *database)
{
  if (database == nullptr)
    std::cout << "null in store_access_record";

  return store_record(read_access_record(line), database);

  // access_record record = read_access_record(line);
  // std::cout << std::endl;
  // std::cout << line << std::endl;
  // std::cout << "Remote address:\t\t" << record.remote_address << std::endl;
  // std::cout << "Remote user:\t\t" << record.remote_user << std::endl;
  // std::cout << "Local time:\t\t" << record.time.local_time << " " << record.time.timezone << std::endl;
  // std::cout << "Request method:\t\t" << record.request.method << std::endl;
  // std::cout << "Request path:\t\t" << record.request.path << std::endl;
  // std::cout << "Request query:\t\t" << record.request.query << std::endl;
  // std::cout << "Request fragment:\t" << record.request.fragment << std::endl;
  // std::cout << "Request version:\t" << record.request.version << std::endl;
  // std::cout << "Request status:\t\t" << record.http_status_code << std::endl;
  // std::cout << "Bytes sent:\t\t" << record.bytes_sent << std::endl;
  // std::cout << "Referrer:\t\t" << record.referrer.protocol << "://" << record.referrer.authentication << record.referrer.domain << ":" << record.referrer.port << std::endl;
  // std::cout << "Browser:\t\t" << record.user_agent.browser_name << "/" << record.user_agent.browser_version << std::endl;
  // std::cout << "Rendering engine:\t" << record.user_agent.rendering_engine_name << "/" << record.user_agent.rendering_engine_version << std::endl;
  // std::cout << "Operating system:\t" << record.user_agent.operating_system << " on " + record.user_agent.device_type + std::endl;
}

int main()
{
  sqlite3 *database;
  std::fstream file;
  std::string database_path = "../data/stats.db";
  std::string log_path = "../../proxy/logs/access.log";

  if (sqlite3_open_v2(database_path.c_str(), &database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr))
  {
    std::cerr << "ERROR: Could not open database: " << sqlite3_errmsg(database) << std::endl;
    return EXIT_FAILURE;
  }

  if (initialize_database(database))
  {
    std::cerr << "ERROR: Could not initialize database: " << sqlite3_errmsg(database) << std::endl;
    return EXIT_FAILURE;
  }

  file.open(log_path, std::ios::in);
  if (!file.is_open())
  {
    std::cerr << "ERROR: Could not open file: " << log_path << std::endl;
    return EXIT_FAILURE;
  }

  if (read_lines(file, store_access_record, database) != EXIT_SUCCESS)
  {
    std::cerr << "ERROR: Error writing to database: " << sqlite3_errmsg(database) << std::endl;
    return EXIT_FAILURE;
  };

  file.close();
  sqlite3_close(database);

  return EXIT_SUCCESS;
}