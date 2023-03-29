#include "reverse_string.h"
#include <algorithm>
using namespace std;

string reverse_string(string string_to_reverse)
{
  string text = string_to_reverse;

  reverse(text.begin(), text.end());

  return text;
};