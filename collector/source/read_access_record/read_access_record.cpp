#include "read_access_record.h"
#include "segment_default_access_record/segment_default_access_record.h"
#include "segment_to_moment/segment_to_moment.h"
#include "segment_to_http_request/segment_to_http_request.h"
#include "segment_to_url/segment_to_url.h"
using namespace std;

access_record read_access_record(string line)
{
  access_record record;
  access_record_segments segments = segment_default_access_record(line);

  record.remote_address = segments.remote_address;
  record.remote_user = segments.remote_user;
  record.time = segment_to_moment(segments.local_time);
  record.request = segment_to_http_request(segments.http_request);

  record.http_status_code = segments.http_status_code.length() > 0 ? stoi(segments.http_status_code) : 0;
  record.bytes_sent = segments.bytes_sent.length() > 0 ? stoi(segments.bytes_sent) : 0;
  record.referrer = segment_to_url(segments.referrer);
  record.user_agent = segments.user_agent;

  return record;
}
