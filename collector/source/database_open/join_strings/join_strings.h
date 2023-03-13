#ifndef JOIN_STRINGS_H
#define JOIN_STRINGS_H

#include <string>
using namespace std;

template <size_t length>
string join_strings(string (&strings)[length], string delimiter)
{
  string joined;

  for (string str : strings)
    joined = joined + str + delimiter;

  joined.erase(joined.length() - delimiter.length());

  return joined;
};

#endif