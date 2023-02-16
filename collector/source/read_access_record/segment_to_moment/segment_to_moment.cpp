#include "segment_to_moment.h"
#include "pad_left/pad_left.h"
#include "month_string_to_int/month_string_to_int.h"
#include "../first_capture_group/first_capture_group.h"
using namespace std;

moment segment_to_moment(string segment)
{
  moment moment;
  char padding = '0';

  // Example: 22/Jan/2023
  string day_pattern = "\\d{1,2}";
  string month_pattern = "\\w{3}";
  string year_pattern = "\\d{1,4}";
  string date_pattern = day_pattern + "\\/" + month_pattern + "\\/" + year_pattern;

  // Example: 14:11:17
  string hours_pattern = "\\d{1,2}";
  string minutes_pattern = "\\d{1,2}";
  string seconds_pattern = "\\d{1,2}";
  string timestamp_pattern = hours_pattern + ":" + minutes_pattern + ":" + seconds_pattern;

  // Example: +0000
  string timezone_pattern = "[\\+|-]\\d{4}";

  // Example: 22/Jan/2023:14:11:17 +0000
  string day = first_capture_group("^(" + day_pattern + ")\\/", segment);
  string month = first_capture_group("^" + day_pattern + "\\/(" + month_pattern + ")", segment);
  string year = first_capture_group("^" + day_pattern + "\\/" + month_pattern + "\\/(" + year_pattern + ")", segment);
  string hours = first_capture_group("^" + date_pattern + ":(" + hours_pattern + ")", segment);
  string minutes = first_capture_group("^" + date_pattern + ":" + hours_pattern + ":(" + minutes_pattern + ")", segment);
  string seconds = first_capture_group("^" + date_pattern + ":" + hours_pattern + ":" + minutes_pattern + ":(" + seconds_pattern + ")", segment);
  string timezone = first_capture_group("^" + date_pattern + ":" + timestamp_pattern + " (" + timezone_pattern + ")", segment);

  // Example: 0000-00-00
  string date_day = pad_left(day, padding, 2);
  string date_month = pad_left(to_string(month_string_to_int(month)), padding, 2);
  string date_year = pad_left(year, padding, 4);
  string date = date_year + "-" + date_month + "-" + date_day;

  // Example: 00:00:00
  string timestamp_hours = pad_left(hours, padding, 2);
  string timestamp_minutes = pad_left(minutes, padding, 2);
  string timestamp_seconds = pad_left(seconds, padding, 2);
  string timestamp = timestamp_hours + ":" + timestamp_minutes + ":" + timestamp_seconds;

  moment.local_time = date + " " + timestamp;
  moment.timezone = timezone;

  return moment;
};