#ifndef SEGMENT_DEFAULT_ACCESS_RECORD_H
#define SEGMENT_DEFAULT_ACCESS_RECORD_H

#include <string>
#include <regex>
using namespace std;

struct access_record_segments
{
  string remote_address;
  string remote_user;
  string local_time;
  string http_request;
  string http_status_code;
  string bytes_sent;
  string referrer;
  string user_agent;
};

access_record_segments segment_default_access_record(string line);

#endif