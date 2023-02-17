#ifndef FIND_BROWSER_H
#define FIND_BROWSER_H

#include <string>

struct browser
{
  std::string name;
  std::string version;
};

browser find_browser(std::string agent);

#endif