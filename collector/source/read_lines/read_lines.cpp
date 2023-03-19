#include "read_lines.h"
#include "process_reversed_line/process_reversed_line.h"
#include "get_last_record_string/get_last_record_string.h"
using namespace std;

extern const int EARLY_RETURN;

int read_lines(istream &input, function<int(string, vector<string>, sqlite3 *)> process, sqlite3 *database)
{
  string line;
  vector<string> last_record_string = get_last_record_string(database);
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
      int exit_code = process_reversed_line(process, line, last_record_string, database);

      if (exit_code == EARLY_RETURN)
        return EXIT_SUCCESS;

      if (exit_code != EXIT_SUCCESS)
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

  return process_reversed_line(process, line, last_record_string, database);
}