#ifndef SEGMENT_TO_HTTP_REQUEST_H
#define SEGMENT_TO_HTTP_REQUEST_H

#include <string>
#include <regex>
using namespace std;

struct http_request
{
  string method;
  string path;
  string query;
  string fragment;
  string version;
};

http_request segment_to_http_request(string segment);

#endif