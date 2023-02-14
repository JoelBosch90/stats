#include "segment_default_access_record.h"

access_record_segments segment_default_access_record(string line)
{
  access_record_segments segments;
  stringstream access_record;
  smatch parts;

  string ip = "(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}|-)";
  string numeric = "(\\d*)";
  string quoted = "\"(.*?)\"";
  string bracketed = "\\[(.*?)\\]";

  // // Example: http://localhost:8009/
  // // Example: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0
  // string string = "\"(.*)\"";

  // Example: 172.21.0.1 - -
  access_record << ip << " - " << ip << " "
                // Example: [22/Jan/2023:14:11:17 +0000]
                << bracketed << " "
                // Example: "GET /build/bundle.css HTTP/1.1"
                << quoted << " "
                // Example: 304
                << numeric << " "
                // Example: 0
                << numeric << " "
                // "http://localhost:8009/"
                << quoted << " "
                // "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0"
                << quoted;

  regex expression(access_record.str());
  regex_search(line, parts, expression);

  segments.remote_address = parts[1];
  segments.remote_user = parts[2];
  segments.local_time = parts[3];
  segments.http_request = parts[4];
  segments.http_status_code = parts[5];
  segments.bytes_sent = parts[6];
  segments.referrer = parts[7];
  segments.user_agent = parts[8];

  return segments;
}