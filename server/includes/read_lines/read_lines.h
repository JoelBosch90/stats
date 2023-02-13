#ifndef READ_LINES_H
#define READ_LINES_H

#include <istream>
#include <algorithm>
#include <string>
#include <functional>
using namespace std;

void read_lines(istream &input, function<void(string)> process);

#endif