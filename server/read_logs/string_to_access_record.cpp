#include "string_to_access_record.h"

regex default_access_record_expression()
{
  // Example: 172.21.0.1
  // Example: -
  string ip = "(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}|-)";

  // Example: 22/Jan/2023
  string date = "\\d{1,2}\\/\\w{3}\\/\\d{1,4}";
  // Example: 14:11:17
  string time = "\\d{1,2}:\\d{1,2}:\\d{1,2}";
  // Example: +0000
  string timezone = "[\\+|-]\\d{4}";
  // Example: 22/Jan/2023:14:11:17 +0000
  string local_time = "\\[(" + date + ":" + time + " " + timezone + ")\\]";

  // Example: GET
  string request_type = "\\w{3,7}";
  // Example: /build/bundle.css
  string url = "\\/.*";
  // Example: HTTP/1.1
  string http_version = "HTTP\\/[\\d\\.]+";
  // Example: GET /build/bundle.css HTTP/1.1
  string request = "\"(" + request_type + " " + url + " " + http_version + ")\"";

  // Example: 304
  string status = "(\\d{3})";

  // Example: 0
  string bytes = "(\\d+)";

  // Example: http://localhost:8009/
  // Example: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0
  string string = "\"(.*)\"";

  stringstream log_line;
  // Example: 172.21.0.1 - - [22/Jan/2023:14:11:17 +0000] "GET /build/bundle.css HTTP/1.1" 304 0 "http://localhost:8009/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0"
  log_line << ip << " - " << ip << " " << local_time << " " << request << " " << status << " " << bytes << " " << string << " " << string;

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
