#include "process_reversed_line.h"
#include "only_whitespaces/only_whitespaces.h"
#include <algorithm>
using namespace std;

int process_reversed_line(function<int(string, vector<string>, sqlite3 *)> process, string line, vector<string> last_local_time, sqlite3 *database)
{
  if (only_whitespaces(line))
    return EXIT_SUCCESS;

  reverse(line.begin(), line.end());
  return process(line, last_local_time, database);
}