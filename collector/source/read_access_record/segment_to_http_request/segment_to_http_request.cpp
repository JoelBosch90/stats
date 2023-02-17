#include "segment_to_http_request.h"
#include "../first_capture_group/first_capture_group.h"
using namespace std;

// Example segment: GET /home/page.html?question=answer&key=value#anchor HTTP/1.1
http_request segment_to_http_request(string segment)
{
  http_request request;
  string method = "\\w{3,7}";

  request.full_text = segment;
  // Example: GET
  request.method = first_capture_group("^(" + method + ")", segment);
  // Example: /home/page.html
  request.path = first_capture_group("^" + method + " ([^\\s ?#]*)", segment);
  // Example: ?question=answer&key=value
  request.query = first_capture_group("\\?([^\\s#]*)", segment);
  // Example: #anchor
  request.fragment = first_capture_group("#([^\\s?]*)", segment);
  // Example: HTTP/1.1
  request.version = first_capture_group(" (HTTP\\/[\\d\\.]+)$", segment);

  return request;
};