#include "store_latest_logs/store_latest_logs.h"
#include "repeat/repeat.h"
#include <iostream>
#include <vector>
#include <functional>
#include <sodium.h>
#include <cstdlib>

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
  const std::string database_path = "/data/" + (database_name_env ? database_name_env : DEFAULT_DATABASE_NAME);
  const std::string logfile_path = "/logs/" + (logfile_name_env ? logfile_name_env : DEFAULT_LOGFILE_NAME);
  const int update_interval = update_interval_env ? std::atoi(update_interval_env) : DEFAULT_UPDATE_INTERVAL;

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
      { store_latest_logs(logfile_path, database_path); },
      update_interval};
  std::vector<repeated_task> tasks = {store_latest_logs_task};

  // By repeating the store_latest_logs_task at a steady interval, we make sure
  // that the database is kept up to date with the latest logs, even if the log
  // file gets periodically purged. This makes sure that we have a way to
  // quickly and efficiently access the access logs data.
  repeat(tasks);

  return EXIT_SUCCESS;
}