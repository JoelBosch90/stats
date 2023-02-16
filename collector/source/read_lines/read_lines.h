#ifndef READ_LINES_H
#define READ_LINES_H

#include <istream>
#include <algorithm>
#include <string>
#include <functional>

void read_lines(std::istream &input, std::function<void(std::string)> process);

#endif