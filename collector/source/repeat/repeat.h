#ifndef REPEAT_H
#define REPEAT_H

#include <functional>
#include <vector>

struct repeated_task
{
  std::function<void()> function;
  int interval_in_milliseconds;
};

void repeat(const std::vector<repeated_task> &tasks);

#endif