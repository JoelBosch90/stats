#include "read_lines.h"
#include "only_whitespaces/only_whitespaces.h"
#include "reverse_string/reverse_string.h"
#include "reverse_access_record_vector/reverse_access_record_vector.h"
using namespace std;

vector<access_record> read_lines(istream &input, string until, sqlite3 *database)
{
  vector<access_record> output_lines;
  string line;
  access_record record;
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
      if (!only_whitespaces(line))
      {
        // Because we read from the end, the line will be reversed. We should
        // turn it around. We want to read the time stamp, so we process the
        // record here.
        record = read_access_record(reverse_string(line), database);

        // Check if we've reached the until timestamp and stop reading.
        if (record.time.local_time < until)
          return reverse_access_record_vector(output_lines);

        output_lines.push_back(record);
      }

      line.clear();
    }
    else
    {
      line.push_back(next_char);
    }

    // Move the position of the reader back one character.
    input.seekg(-1, ios::cur);
  }

  // Because we read from the end, the line will be reversed. We should
  // turn it around. We want to read the time stamp, so we process the
  // record here.
  record = read_access_record(reverse_string(line), database);

  // Include the last read line if it is still after the until timestamp.
  if (record.time.local_time >= until)
    output_lines.push_back(record);

  return reverse_access_record_vector(output_lines);
}