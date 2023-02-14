#include "month_string_to_int.h"

int month_string_to_int(string month)
{
  if (month == "Jan")
    return 1;
  if (month == "Feb")
    return 2;
  if (month == "Mar")
    return 3;
  if (month == "Apr")
    return 4;
  if (month == "May")
    return 5;
  if (month == "Jun")
    return 6;
  if (month == "Jul")
    return 7;
  if (month == "Aug")
    return 8;
  if (month == "Sep")
    return 9;
  if (month == "Oct")
    return 10;
  if (month == "Nov")
    return 11;
  if (month == "Dec")
    return 12;

  // Something has gone wrong if we reach this point.
  return 0;
};