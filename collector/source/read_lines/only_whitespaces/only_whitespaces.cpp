#include "only_whitespaces.h"
using namespace std;

bool only_whitespaces(string input)
{
  return input.find_first_not_of(" \t\n\v\f\r") == string::npos;
}