#ifndef TIME_POINT_TO_STRING_H
#define TIME_POINT_TO_STRING_H

#include <string>
#include <chrono>

std::string time_point_to_string(std::chrono::system_clock::time_point time_point);

#endif