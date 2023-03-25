#include "segment_to_agent.h"
#include "find_browser/find_browser.h"
#include "find_rendering_engine/find_rendering_engine.h"
#include "find_operating_system/find_operating_system.h"
#include "find_device_type/find_device_type.h"
using namespace std;

// Example: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0
agent segment_to_agent(string segment)
{
  agent user_agent;
  browser user_browser = find_browser(segment);
  rendering_engine user_rendering_engine = find_rendering_engine(segment);

  user_agent.full_text = segment;
  user_agent.browser_name = user_browser.name;
  user_agent.browser_version = user_browser.version;
  user_agent.rendering_engine_name = user_rendering_engine.name;
  user_agent.rendering_engine_version = user_rendering_engine.version;
  user_agent.operating_system = find_operating_system(segment);
  user_agent.device_type = find_device_type(segment);

  return user_agent;
};