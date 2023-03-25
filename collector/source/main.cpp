#include "store_latest_logs/store_latest_logs.h"
#include "repeat/repeat.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <functional>

extern const int EARLY_RETURN = -1;

int main()
{
  const std::string DATABASE_PATH = "../data/stats.db";
  const std::string LOGFILE_PATH = "../../proxy/logs/access.log";

  repeated_task store_latest_logs_task = {
      [&]()
      { store_latest_logs(LOGFILE_PATH, DATABASE_PATH); },
      60000};

  std::vector<repeated_task> tasks = {store_latest_logs_task};

  repeat(tasks);

  return EXIT_SUCCESS;
}