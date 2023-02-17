#include "find_browser.h"
#include <regex>
using namespace std;

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Browser_detection_using_the_user_agent#browser_name
browser find_browser(string agent)
{
  browser user_browser;
  smatch matches;

  if (regex_search(agent, matches, regex("Edg.*/([\\d\\.]+)")))
  {
    user_browser.name = "Edge";
    user_browser.version = matches[1];

    return user_browser;
  };

  for (string browser_name : {"Seamonkey", "Chromium", "Chrome", "Firefox", "Safari", "Opera"})
  {
    if (regex_search(agent, matches, regex("(" + browser_name + ")/([\\d\\.]+)")))
    {
      user_browser.name = matches[1];
      user_browser.version = matches[2];

      return user_browser;
    };
  }

  if (regex_search(agent, matches, regex("OPR/([\\d\\.]+)")))
  {
    user_browser.name = "Opera";
    user_browser.version = matches[1];

    return user_browser;
  };

  if (regex_search(agent, matches, regex("; MSIE ([\\d\\.]+);")))
  {
    user_browser.name = "Internet Explorer";
    user_browser.version = matches[1];

    return user_browser;
  };

  if (regex_search(agent, matches, regex("Trident/7.0; .*rv:([\\d\\.]+)")))
  {
    user_browser.name = "Internet Explorer";
    user_browser.version = matches[1];
  };

  return user_browser;
};