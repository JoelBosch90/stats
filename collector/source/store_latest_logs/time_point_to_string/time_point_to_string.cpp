#include "time_point_to_string.h"
#include <iomanip>
using namespace std;

string time_point_to_string(chrono::system_clock::time_point time_point)
{
  time_t time_t = chrono::system_clock::to_time_t(time_point);
  tm tm = *std::localtime(&time_t);
  ostringstream stringstream;

  stringstream << put_time(&tm, "%Y-%m-%d %H:%M:%S");

  return stringstream.str();
}