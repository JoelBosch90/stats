#include "find_rendering_engine.h"
#include <regex>
using namespace std;

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Browser_detection_using_the_user_agent#rendering_engine
rendering_engine find_rendering_engine(string agent)
{
  rendering_engine user_rendering_engine;
  smatch engine_matches;
  smatch version_matches;

  if (regex_search(agent, engine_matches, regex("Gecko/([\\d\\.]+)")))
  {
    user_rendering_engine.name = "Gecko";
    user_rendering_engine.version = regex_search(agent, version_matches, regex("rv:([\\d\\.]+)")) ? version_matches[1] : engine_matches[1];

    return user_rendering_engine;
  }

  if (regex_search(agent, engine_matches, regex("AppleWebKit/([\\d\\.]+)")))
  {
    user_rendering_engine.name = "WebKit";
    user_rendering_engine.version = engine_matches[1];

    return user_rendering_engine;
  }

  if (regex_search(agent, engine_matches, regex("Opera/([\\d\\.]+)")))
  {
    user_rendering_engine.name = "Presto";
    user_rendering_engine.version = engine_matches[1];

    return user_rendering_engine;
  }

  if (regex_search(agent, engine_matches, regex("Trident/([\\d\\.]+)")))
  {
    user_rendering_engine.name = "Trident";
    user_rendering_engine.version = engine_matches[1];

    return user_rendering_engine;
  }

  if (regex_search(agent, engine_matches, regex("Edge/([\\d\\.]+)")))
  {
    user_rendering_engine.name = "EdgeHTML";
    user_rendering_engine.version = engine_matches[1];

    return user_rendering_engine;
  }

  if (regex_search(agent, engine_matches, regex("Chrome/([\\d\\.]+)")))
  {
    user_rendering_engine.name = "Blink";
    user_rendering_engine.version = engine_matches[1];

    return user_rendering_engine;
  }

  return user_rendering_engine;
};