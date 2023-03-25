#include "get_daily_salt.h"
#include "get_current_salt/get_current_salt.h"
#include "generate_new_salt/generate_new_salt.h"
#include "insert_new_salt/insert_new_salt.h"
using namespace std;

string get_daily_salt(sqlite3 *database)
{
  string salt = get_current_salt(database);

  if (salt == "")
  {
    salt = generate_new_salt();

    insert_new_salt(salt, database);
  }

  return salt;
};