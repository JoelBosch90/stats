#include "reverse_access_record_vector.h"
#include <algorithm>
using namespace std;

vector<access_record> reverse_access_record_vector(vector<access_record> vector_to_reverse)
{
  vector<access_record> vector = vector_to_reverse;

  reverse(vector.begin(), vector.end());

  return vector;
};