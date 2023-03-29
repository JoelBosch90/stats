#include "process_reversed_line.h"
#include <algorithm>
#include <iostream>
using namespace std;

extern const int EARLY_RETURN;

int process_reversed_line(function<int(string, vector<string>, sqlite3 *)> process, string line, vector<string> last_local_time, sqlite3 *database)
{
  std::cout << "LINE: " << line << std::endl;

  reverse(line.begin(), line.end());

  int exit_code = process(line, last_local_time, database);

  if (exit_code != EARLY_RETURN && exit_code != EXIT_SUCCESS)
    cerr << "ERROR: Error writing to database: " << sqlite3_errmsg(database) << endl;

  return exit_code;
}