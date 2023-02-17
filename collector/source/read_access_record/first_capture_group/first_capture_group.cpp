#include "first_capture_group.h"
#include <regex>
using namespace std;

string first_capture_group(string pattern, string source)
{
  smatch matches;
  regex expression(pattern);
  bool found = regex_search(source, matches, expression);

  if (found && matches.length() > 1)
    return matches[1];

  return "";
};