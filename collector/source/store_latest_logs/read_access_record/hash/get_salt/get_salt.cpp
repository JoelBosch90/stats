#include "get_salt.h"
#include "get_dated_salt/get_dated_salt.h"
#include "generate_new_salt/generate_new_salt.h"
#include "insert_new_salt/insert_new_salt.h"
using namespace std;

string get_salt(string timestamp, sqlite3 *database)
{
  string salt = get_dated_salt(timestamp, database);

  if (salt == "")
  {
    salt = generate_new_salt();

    insert_new_salt(salt, timestamp, database);
  }

  return salt;
};