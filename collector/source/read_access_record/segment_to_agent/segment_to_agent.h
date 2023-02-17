#ifndef SEGMENT_TO_AGENT_H
#define SEGMENT_TO_AGENT_H

#include <string>

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Browser_detection_using_the_user_agent
struct agent
{
  std::string full_text;
  std::string browser_name;
  std::string browser_version;
  std::string rendering_engine_name;
  std::string rendering_engine_version;
  std::string operating_system;
  std::string device_type;
};

agent segment_to_agent(std::string segment);

#endif