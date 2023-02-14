#include <iostream>
#include "segment_to_moment.h"
#include "pad_left/pad_left.h"
#include "month_string_to_int/month_string_to_int.h"

moment segment_to_moment(string segment)
{
  moment moment;
  smatch parts;

  string day_pattern = "\\d{1,2}";
  string month_pattern = "\\w{3}";
  string year_pattern = "\\d{1,4}";
  string hours_pattern = "\\d{1,2}";
  string minutes_pattern = "\\d{1,2}";
  string seconds_pattern = "\\d{1,2}";
  string timezone_pattern = "[\\+|-]\\d{4}";

  // Example: 22/Jan/2023:14:11:17 +0000
  stringstream local_time;
  local_time << day_pattern << "\\/" << month_pattern << "\\/" << year_pattern
             << ":" << hours_pattern << ":" << minutes_pattern << ":" << seconds_pattern
             << " " << timezone_pattern;

  regex expression(local_time.str());
  regex_search(segment, parts, expression);

  char padding = '0';

  // Example: 0000-00-00
  string day = pad_left(parts[1], padding, 2);
  string month = pad_left(to_string(month_string_to_int(parts[2])), padding, 2);
  string year = pad_left(parts[3], padding, 4);
  string date = year + "-" + month + "-" + day;

  // Example: 00:00:00
  string hours = pad_left(parts[4], padding, 2);
  string minutes = pad_left(parts[5], padding, 2);
  string seconds = pad_left(parts[6], padding, 2);
  string time = hours + ":" + minutes + ":" + seconds;

  moment.local_time = date + " " + time;
  moment.timezone = parts[7];

  return moment;
};