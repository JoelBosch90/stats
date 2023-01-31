#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "string_to_access_record.h"
#include "read_lines_from_stream_from_end.h"
using namespace std;

void print_access_record(string line)
{
  default_access_record record = string_to_access_record(line);

  cout << "Remote address:\t" << record.remote_address << "\n";
  cout << "Remote user:\t" << record.remote_user << "\n";
  cout << "Local time:\t" << record.local_time << "\n";
  cout << "Request:\t" << record.request << "\n";
  cout << "Status:\t\t" << record.status << "\n";
  cout << "Bytes sent:\t" << record.bytes_sent << "\n";
  cout << "Referrer:\t" << record.referrer << "\n";
  cout << "User agent:\t" << record.user_agent << "\n";
}

int main()
{
  fstream file;

  file.open("./../proxy/logs/access.log", ios::in);

  if (file.is_open())
  {
    read_lines_from_stream_from_end(file, print_access_record);

    file.close();
  }

  return EXIT_SUCCESS;
}