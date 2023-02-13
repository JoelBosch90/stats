#include "only_whitespaces.h"

bool only_whitespaces(string input)
{
  return input.find_first_not_of(" \t\n\v\f\r") == string::npos;
}