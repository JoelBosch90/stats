#include "string_to_access_record.h"

regex default_access_record_expression()
{
  string ip = "(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}|-)";

  string date = "\\d{1,2}\\/\\w{3}\\/\\d{1,4}";
  string time = "\\d{1,2}:\\d{1,2}:\\d{1,2}";
  string timezone = "[\\+|-]\\d{4}";
  string local_time = "\\[(" + date + ":" + time + " " + timezone + ")\\]";

  string request_type = "\\w{3,7}";
  string url = "\\/.*";
  string http_version = "HTTP\\/[\\d\\.]+";
  string request = "\"(" + request_type + " " + url + " " + http_version + ")\"";

  string status = "(\\d{3})";

  string bytes = "(\\d+)";

  string referrer = "\"(.*)\"";

  string user_agent = "\"(.*)\"";

  stringstream log_line;
  log_line << ip << " - " << ip << " " << local_time << " " << request << " " << status << " " << bytes << " " << referrer << " " << user_agent;

  regex expression(log_line.str());
  return expression;
}

default_access_record string_to_access_record(string line)
{
  regex expression = default_access_record_expression();
  smatch parts;
  default_access_record record;

  regex_search(line, parts, expression);

  record.remote_address = parts[1];
  record.remote_user = parts[2];
  record.local_time = parts[3];
  record.request = parts[4];
  record.status = parts[5];
  record.bytes_sent = parts[6];
  record.referrer = parts[7];
  record.user_agent = parts[8];

  return record;
}
