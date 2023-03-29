#include "subtract_day_from_string.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

string subtract_day_from_string(string original_timestamp)
{
  // Convert string to time_point.
  std::tm input_time = {};
  std::istringstream input_string_stream(original_timestamp);
  input_string_stream >> std::get_time(&input_time, "%Y-%m-%d %H:%M:%S");
  std::chrono::time_point<std::chrono::system_clock> time_point = std::chrono::system_clock::from_time_t(std::mktime(&input_time));

  // Subtract one day.
  auto one_day = std::chrono::hours(24);
  time_point -= one_day;

  // Convert time_point back to string.
  std::time_t output_time = std::chrono::system_clock::to_time_t(time_point);
  std::stringstream output_string_stream;
  output_string_stream << std::put_time(std::localtime(&output_time), "%Y-%m-%d %H:%M:%S");

  return output_string_stream.str();
};