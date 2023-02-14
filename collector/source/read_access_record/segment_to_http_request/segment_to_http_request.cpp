#include "segment_to_http_request.h"
#include <iostream>

http_request segment_to_http_request(string segment)
{
  string random = "GET /home/page.html?question=answer&key=value#anchor HTTP/1.1";
  http_request request;
  smatch parts;

  // Example: GET
  string method = "\\w{3,7}";
  // Example: /home/page.html
  string path = "\\/\\S*";
  // Example: ?question=answer&key=value
  string query = "\\?([^\\s#])";
  // Example: #anchor
  string fragment = "#([^\\s])";
  // Example: HTTP/1.1
  string http_version = "HTTP\\/[\\d\\.]+";

  // Example: GET /home/page.html?question=answer&key=value#anchor HTTP/1.1
  regex expression(method + " " + path + query + fragment + " " + http_version);
  regex_search(random, parts, expression);

  request.method = parts[1];
  request.path = parts[2];
  request.query = parts[3];
  request.fragment = parts[4];
  request.version = parts[5];

  return request;
};