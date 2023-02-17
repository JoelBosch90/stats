#include <regex>
#include "segment_default_access_record.h"
#include "../first_capture_group/first_capture_group.h"
using namespace std;

// Example: 172.21.0.1 - - [22/Jan/2023:14:11:17 +0000] "GET /build/bundle.css HTTP/1.1" 304 0 "http://localhost:8009/" "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0"
access_record_segments segment_default_access_record(string line)
{
  access_record_segments segments;
  stringstream access_record;
  smatch parts;

  string ip = "\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}|-";
  string http_request = "\\w{3,7} .*? HTTP/[\\d\\.]+";
  string numeric = "\\d*";
  string anything = ".*?";
  string anything_quoted = "\".*?\"";

  segments.full_text = line;
  // Example: 172.21.0.1 - -
  segments.remote_address = first_capture_group("(" + ip + ") - (?:" + ip + ")", line);
  // Example: - - 172.21.0.1
  segments.remote_user = first_capture_group("(?:" + ip + ") - (" + ip + ")", line);
  // Example: [22/Jan/2023:14:11:17 +0000]
  segments.local_time = first_capture_group("\\[(" + anything + ")\\]", line);
  // Example: "GET /build/bundle.css HTTP/1.1"
  segments.http_request = first_capture_group("\"(" + http_request + ")\"", line);
  // Example: 304
  segments.http_status_code = first_capture_group("\"" + http_request + "\" (\\d{3})", line);
  // Example: 0
  segments.bytes_sent = first_capture_group("\"" + http_request + "\" \\d{3} (\\d+)", line);
  // "http://localhost:8009/"
  segments.referrer = first_capture_group("\"" + http_request + "\".*?\"(" + anything + ")\"", line);
  // "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0"
  segments.user_agent = first_capture_group(anything_quoted + anything + anything_quoted + anything + "\"(" + anything + ")\"", line);

  return segments;
}