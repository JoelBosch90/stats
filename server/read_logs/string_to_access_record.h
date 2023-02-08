#ifndef LOG_LINE_TO_STRUCT_H
#define LOG_LINE_TO_STRUCT_H

#include <string>
#include <regex>
using namespace std;

struct default_access_record
{
  string remote_address;
  string remote_user;
  string local_time;
  string request;
  string status;
  string bytes_sent;
  string referrer;
  string user_agent;
};

default_access_record string_to_access_record(string line);

#endif