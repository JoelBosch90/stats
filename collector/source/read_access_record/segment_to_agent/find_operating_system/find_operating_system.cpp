#include "find_operating_system.h"
#include <regex>
using namespace std;

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Browser_detection_using_the_user_agent#os
string find_operating_system(string agent)
{
  smatch matches;

  if (regex_search(agent, matches, regex("(Android ?[\\d\\.]+)")))
    return matches[1];

  if (regex_search(agent, matches, regex("(Windows[^;\\)]+)")))
    return matches[1];

  if (regex_search(agent, matches, regex("(?:\\(|; )([^;\\)]+Mac OS[^;\\)]+)")))
    return matches[1];

  if (regex_search(agent, matches, regex("Linux")))
    return matches[1];

  return "Unknown";
};