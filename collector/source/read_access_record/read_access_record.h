#ifndef READ_ACCESS_RECORD_H
#define READ_ACCESS_RECORD_H

#include <string>
#include <regex>
#include "segment_to_moment/segment_to_moment.h"
#include "segment_to_http_request/segment_to_http_request.h"
using namespace std;

struct referrer
{
  string protocol;
  string domain;
  string port;
};

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Browser_detection_using_the_user_agent
// struct user_agent
// {
//   string text;
//   string browser_name;
//   string browser_version;
//   string rendering_engine_name;
//   string rendering_engine_version;
//   string operating_system;
//   string device_type;
// };

struct access_record
{
  int id;
  string remote_address;
  string remote_user;
  moment time;
  http_request request;
  int http_status_code;
  int bytes_sent;
  // referrer referrer;
  string user_agent;
};

access_record read_access_record(string line);

#endif