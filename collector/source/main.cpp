#include "store_latest_logs/store_latest_logs.h"

extern const int EARLY_RETURN = -1;

int main()
{
  std::string DATABASE_PATH = "../data/stats.db";
  std::string LOGFILE_PATH = "../../proxy/logs/access.log";

  return store_latest_logs(LOGFILE_PATH, DATABASE_PATH);
}