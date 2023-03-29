#include "segment_to_url.h"
#include "../first_capture_group/first_capture_group.h"
#include "../hash/hash.h"

// Example: protocol://username:password@domain.com:3000/this/is/a/path?query=true#anchor
url segment_to_url(std::string segment, std::string timestamp, sqlite3 *database)
{
  url link;

  link.full_text = segment;
  link.protocol = first_capture_group("^(.*?)://", segment);
  std::string authentication_plus_domain = first_capture_group("://([^\\s#?/@]+@[^\\s#?/:@]+|[^\\s#?/:@]+)", segment);
  link.authentication = hash(first_capture_group("(.*?)@", authentication_plus_domain), timestamp, database);
  link.domain = first_capture_group("([^@/:\\s?#]+?)$", authentication_plus_domain);
  link.port = first_capture_group(":(\\d{1,5})[/?:#]|$", segment);
  link.query = first_capture_group("\\?([^#]*)(?:#|$)", segment);
  link.fragment = first_capture_group("#([^?\\s])\\?|$", segment);

  return link;
};