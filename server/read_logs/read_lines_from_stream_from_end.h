#ifndef READ_LINES_FROM_STREAM_FROM_END_H
#define READ_LINES_FROM_STREAM_FROM_END_H

#include <istream>
#include <algorithm>
#include <string>
#include <functional>
using namespace std;

void read_lines_from_stream_from_end(istream &input, function<void(string)> process);

#endif