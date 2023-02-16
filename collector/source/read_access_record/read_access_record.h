#ifndef READ_ACCESS_RECORD_H
#define READ_ACCESS_RECORD_H

#include <string>
#include "segment_to_moment/segment_to_moment.h"
#include "segment_to_http_request/segment_to_http_request.h"
#include "segment_to_url/segment_to_url.h"
#include "segment_to_agent/segment_to_agent.h"

struct access_record
{
  int id;
  std::string remote_address;
  std::string remote_user;
  moment time;
  http_request request;
  int http_status_code;
  int bytes_sent;
  url referrer;
  agent user_agent;
};

access_record read_access_record(std::string line);

#endif