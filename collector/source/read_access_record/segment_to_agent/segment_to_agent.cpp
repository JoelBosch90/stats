#include "segment_to_agent.h"
#include "../first_capture_group/first_capture_group.h"
using namespace std;

// Example: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0
agent segment_to_agent(string line)
{
  agent user_agent;

  user_agent.text = line;
  user_agent.browser_name;
  user_agent.browser_version;
  user_agent.rendering_engine_name;
  user_agent.rendering_engine_version;
  user_agent.operating_system;
  user_agent.device_type;

  return user_agent;
};