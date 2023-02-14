#include "read_access_record.h"
#include "segment_default_access_record/segment_default_access_record.h"
#include "segment_to_moment/segment_to_moment.h"
#include "segment_to_http_request/segment_to_http_request.h"

access_record read_access_record(string line)
{
  access_record record;
  access_record_segments segments = segment_default_access_record(line);

  record.remote_address = segments.remote_address;
  record.remote_user = segments.remote_user;
  record.time = segment_to_moment(segments.local_time);
  segment_to_http_request(segments.http_request);

  record.http_status_code = stoi(segments.http_status_code);
  record.bytes_sent = stoi(segments.bytes_sent);
  record.user_agent = segments.user_agent;

  return record;
}
