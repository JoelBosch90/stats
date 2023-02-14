#ifndef SEGMENT_TO_MOMENT_H
#define SEGMENT_TO_MOMENT_H

#include <string>
#include <regex>
using namespace std;

struct moment
{
  string local_time;
  string timezone;
};

moment segment_to_moment(string segment);

#endif