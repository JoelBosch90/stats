#include "find_device_type.h"
using namespace std;

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Browser_detection_using_the_user_agent#mobile_tablet_or_desktop
string find_device_type(string agent)
{
  if (agent.find("Tablet") != string::npos)
    return "Tablet";

  if (agent.find("Mobile") != string::npos)
    return "Mobile";

  if (agent.find("Opera Mobi") != string::npos)
    return "Mobile";

  return "Desktop";
};