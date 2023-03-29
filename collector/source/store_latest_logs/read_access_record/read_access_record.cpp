#include "read_access_record.h"
#include "segment_default_access_record/segment_default_access_record.h"
#include "hash/hash.h"

access_record read_access_record(std::string line, sqlite3 *database)
{
  access_record record;
  access_record_segments segments = segment_default_access_record(line);

  record.full_text = line;
  record.time = segment_to_moment(segments.local_time);
  record.remote_address = hash(segments.remote_address, record.time.local_time, database);
  record.remote_user = hash(segments.remote_user, record.time.local_time, database);
  record.request = segment_to_http_request(segments.http_request);
  record.http_status_code = segments.http_status_code.length() > 0 ? stoi(segments.http_status_code) : 0;
  record.bytes_sent = segments.bytes_sent.length() > 0 ? stoi(segments.bytes_sent) : 0;
  record.referrer = segment_to_url(segments.referrer, record.time.local_time, database);
  record.user_agent = segment_to_agent(segments.user_agent);

  return record;
}
