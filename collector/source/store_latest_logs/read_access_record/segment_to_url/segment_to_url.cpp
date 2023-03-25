#include "segment_to_url.h"
#include "../first_capture_group/first_capture_group.h"
using namespace std;

// Example: protocol://username:password@domain.com:3000/this/is/a/path?query=true#anchor
url segment_to_url(string segment)
{
  url link;

  link.full_text = segment;
  link.protocol = first_capture_group("^(.*?)://", segment);
  string authentication_plus_domain = first_capture_group("://([^\\s#?/@]+@[^\\s#?/:@]+|[^\\s#?/:@]+)", segment);
  link.authentication = first_capture_group("(.*?)@", authentication_plus_domain);
  link.domain = first_capture_group("([^@/:\\s?#]+?)$", authentication_plus_domain);
  link.port = first_capture_group(":(\\d{1,5})[/?:#]|$", segment);
  link.query = first_capture_group("\\?([^#]*)(?:#|$)", segment);
  link.fragment = first_capture_group("#([^?\\s])\\?|$", segment);

  return link;
};