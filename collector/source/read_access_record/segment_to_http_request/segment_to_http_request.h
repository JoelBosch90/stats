#ifndef SEGMENT_TO_HTTP_REQUEST_H
#define SEGMENT_TO_HTTP_REQUEST_H

#include <string>

struct http_request
{
  std::string full_text;
  std::string method;
  std::string path;
  std::string query;
  std::string fragment;
  std::string version;
};

http_request segment_to_http_request(std::string segment);

#endif