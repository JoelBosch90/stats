#include "first_capture_group.h"
#include <regex>
using namespace std;

string first_capture_group(string pattern, string source)
{
  smatch parts;
  regex expression(pattern);
  bool found = regex_search(source, parts, expression);

  if (found && parts.length() > 1)
    return parts[1];

  return "";
};