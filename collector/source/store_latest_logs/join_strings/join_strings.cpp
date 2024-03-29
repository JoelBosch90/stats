#include "join_strings.h"
using namespace std;

string join_strings(vector<string> strings, string delimiter)
{
  string joined;

  for (string str : strings)
    joined = joined + str + delimiter;

  joined.erase(joined.length() - delimiter.length());

  return joined;
};