#include "store_latest_logs/store_latest_logs.h"
#include "repeat/repeat.h"
#include <iostream>
#include <vector>
#include <functional>
#include <sodium.h>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <iomanip>

extern const int EARLY_RETURN = -1;

int main()
{
  const int SODIUM_ERROR = -1;

  // The default interval. Note that we measure the interval in milliseconds, so
  // one minute is 60000 miliseconds.
  const int DEFAULT_UPDATE_INTERVAL = 60000;

  // By default, we want to name the database after this application to avoid
  // any confusion.
  const std::string DEFAULT_DATABASE_NAME = "stats.db";

  // By default, the Nginx access log is called 'access.log', so we take this as
  // a default value here.
  const std::string DEFAULT_LOGFILE_NAME = "access.log";

  // Get the environment variables.
  const char *database_name_env = std::getenv("DATABASE_NAME");
  const char *logfile_name_env = std::getenv("LOGFILE_NAME");
  const char *update_interval_env = std::getenv("UPDATE_INTERVAL");

  // Make sure that we use our default values in case the environment variables
  // are not set.
  const std::string production_database_path = "/data/" + (database_name_env ? database_name_env : DEFAULT_DATABASE_NAME);
  const std::string production_logfile_path = "/logs/" + (logfile_name_env ? logfile_name_env : DEFAULT_LOGFILE_NAME);
  const int update_interval = update_interval_env ? std::atoi(update_interval_env) : DEFAULT_UPDATE_INTERVAL;

  // Check to see if we should run in development mode.
  const char *mode = std::getenv("MODE");
  const bool inDevelopmentMode = (mode != nullptr && std::strcmp(mode, "DEVELOPMENT") == 0);

  // Use these alternative paths for easy testing during development.
  const std::string database_path = inDevelopmentMode ? "../data/stats.db" : production_database_path;
  const std::string logfile_path = inDevelopmentMode ? "../../proxy/logs/access.log" : production_logfile_path;

  // We use the Sodium library to generate new salts. To be able to use this, we
  // need to initialize it here.
  if (sodium_init() == SODIUM_ERROR)
  {
    std::cerr << "ERROR: Could not initialize Sodium: " << std::endl;
    return EXIT_FAILURE;
  }

  // We want to read the latest lines in the access.log at a steady interval,
  // and store them in the database. The `store_latest_logs` takes care of
  // reading and storing the latest access logs to the database.
  repeated_task store_latest_logs_task = {
      [&]()
      {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        int number_of_logs_stored = store_latest_logs(logfile_path, database_path);

        if (number_of_logs_stored > 0)
        {
          std::cout << "Imported " << number_of_logs_stored << " new lines at " << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << std::endl;
        }
      },
      update_interval};
  std::vector<repeated_task> tasks = {store_latest_logs_task};

  // By repeating the store_latest_logs_task at a steady interval, we make sure
  // that the database is kept up to date with the latest logs, even if the log
  // file gets periodically purged. This makes sure that we have a way to
  // quickly and efficiently access the access logs data.
  repeat(tasks);

  return EXIT_SUCCESS;
}