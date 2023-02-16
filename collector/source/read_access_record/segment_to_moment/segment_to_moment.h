#ifndef SEGMENT_TO_MOMENT_H
#define SEGMENT_TO_MOMENT_H

#include <string>

struct moment
{
  std::string local_time;
  std::string timezone;
};

moment segment_to_moment(std::string segment);

#endif