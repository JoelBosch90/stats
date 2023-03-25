#ifndef SEGMENT_DEFAULT_ACCESS_RECORD_H
#define SEGMENT_DEFAULT_ACCESS_RECORD_H

#include <string>

struct access_record_segments
{
  std::string full_text;
  std::string remote_address;
  std::string remote_user;
  std::string local_time;
  std::string http_request;
  std::string http_status_code;
  std::string bytes_sent;
  std::string referrer;
  std::string user_agent;
};

access_record_segments segment_default_access_record(std::string line);

#endif