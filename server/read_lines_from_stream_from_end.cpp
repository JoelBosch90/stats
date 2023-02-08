#include "read_lines_from_stream_from_end.h"

bool contains_only_whitespaces(string input)
{
  return input.find_first_not_of(" \t\n\v\f\r") == string::npos;
}

void process_line(string &line, function<void(string)> process)
{
  if (!contains_only_whitespaces(line))
  {
    reverse(line.begin(), line.end());
    process(line);
  }
}

void read_lines_from_stream_from_end(istream &input, function<void(string)> process)
{
  string line;
  char next_char;
  string::iterator line_begin;
  string::iterator line_end;

  // Start looking from the start of the stream to find the position of the
  // beginning.
  input.seekg(0, ios::beg);
  istream::pos_type input_begin = input.tellg();

  // Now move to the end of the stream. We skip the EOF character, so we start
  // with a -1 offset to first the last character before the EOF.
  input.seekg(-1, ios::end);

  // Keep reading the current position until we end up back at the beginning of
  // the stream.
  while (input.tellg() >= input_begin)
  {
    next_char = static_cast<char>(input.peek());

    if (next_char == '\n')
    {
      process_line(line, process);
      line.clear();
    }
    else
    {
      line.push_back(next_char);
    }

    // Move the position of the reader back one character.
    input.seekg(-1, ios::cur);
  }

  process_line(line, process);
}