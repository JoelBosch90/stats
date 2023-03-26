#include "repeat.h"
#include "handle_interrupt/handle_interrupt.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std;

void repeat(const vector<repeated_task> &tasks)
{
  vector<chrono::time_point<chrono::system_clock>> next_times;
  next_times.reserve(tasks.size());

  // While running the loop, we don't want to become unresponsive to system
  // interrupts. Here, we use our `handle_interrupt` function to make sure that
  // we still handle them.
  handle_interrupt();

  // We are keeping a list of when to execute each task next. Initially, we
  // execute all tasks immediately.
  chrono::system_clock::time_point now = chrono::system_clock::now();
  for (const repeated_task &task : tasks)
    next_times.push_back(now);

  while (true)
  {
    // Find the time at which we should execute the next task.
    vector<chrono::system_clock::time_point>::iterator earliest_time = min_element(next_times.begin(), next_times.end());

    // Sleep until the earliest next time we should execute something.
    this_thread::sleep_until(*earliest_time);

    for (int index = 0; index < tasks.size(); index++)
    {
      // Skip executing tasks that should be executed in the future.
      if (next_times[index] > *earliest_time)
        continue;

      tasks[index].function();
      next_times[index] += chrono::milliseconds(tasks[index].interval_in_milliseconds);
    }
  }
};