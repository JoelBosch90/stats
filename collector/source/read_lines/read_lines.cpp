#include "only_whitespaces/only_whitespaces.h"
#include "read_lines.h"
#include <algorithm>
using namespace std;

int process_reversed_line(string line, function<int(string, sqlite3 *)> process, sqlite3 *database)
{
  if (only_whitespaces(line))
    return EXIT_SUCCESS;

  reverse(line.begin(), line.end());
  return process(line, database);
}

int read_lines(istream &input, function<int(string, sqlite3 *)> process, sqlite3 *database)
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
      if (process_reversed_line(line, process, database) != EXIT_SUCCESS)
        return EXIT_FAILURE;

      line.clear();
    }
    else
    {
      line.push_back(next_char);
    }

    // Move the position of the reader back one character.
    input.seekg(-1, ios::cur);
  }

  return process_reversed_line(line, process, database);
}