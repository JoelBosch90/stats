#include "store_latest_logs/store_latest_logs.h"
#include "repeat/repeat.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <sodium.h>

extern const int EARLY_RETURN = -1;

int main()
{
  const int SODIUM_ERROR = -1;
  const int MINUTE_IN_MILLISECONDS = 60000;
  const std::string DATABASE_PATH = "../data/stats.db";
  const std::string LOGFILE_PATH = "../../proxy/logs/access.log";

  if (sodium_init() == SODIUM_ERROR)
  {
    std::cerr << "ERROR: Could not initialize Sodium: " << std::endl;
    return EXIT_FAILURE;
  }

  repeated_task store_latest_logs_task = {
      [&]()
      { store_latest_logs(LOGFILE_PATH, DATABASE_PATH); },
      MINUTE_IN_MILLISECONDS};
  std::vector<repeated_task> tasks = {store_latest_logs_task};

  repeat(tasks);

  return EXIT_SUCCESS;
}