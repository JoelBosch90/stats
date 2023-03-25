#include "remove_all_salts.h"
#include <string>
using namespace std;

int remove_all_salts(sqlite3 *database)
{
  int return_code = sqlite3_exec(database, "DELETE FROM SALTS;", nullptr, nullptr, nullptr);

  return return_code == SQLITE_OK ? EXIT_SUCCESS : EXIT_FAILURE;
};