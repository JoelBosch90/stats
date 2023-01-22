#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

regex default_log_line_expression()
{
  string ip = "(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}|-)";

  string date = "\\d{1,2}\\/\\w{3}\\/\\d{1,4}";
  string time = "\\d{1,2}:\\d{1,2}:\\d{1,2}";
  string timezone = "[\\+|-]\\d{4}";
  string local_time = "\\[(" + date + ":" + time + " " + timezone + ")\\]";

  string request_type = "\\w{3,7}";
  string url = "\\/.*";
  string http_version = "HTTP\\/[\\d\\.]+";
  string request = "\"(" + request_type + " " + url + " " + http_version + ")\"";

  string status = "(\\d{3})";

  string bytes = "(\\d+)";

  string referrer = "\"(.*)\"";

  string user_agent = "\"(.*)\"";

  stringstream log_line;
  log_line << ip << " - " << ip << " " << local_time << " " << request << " " << status << " " << bytes << " " << referrer << " " << user_agent;

  regex expression(log_line.str());
  return expression;
}

int main()
{
  fstream file;

  file.open("./../proxy/logs/access.log", ios::in);

  if (file.is_open())
  {
    string line;
    regex expression = default_log_line_expression();
    smatch parts;

    while (getline(file, line))
    {
      regex_search(line, parts, expression);

      cout << line << "\n";
      cout << "Remote address:\t" << parts[1] << "\n";
      cout << "Remote user:\t" << parts[2] << "\n";
      cout << "Local time:\t" << parts[3] << "\n";
      cout << "Request:\t" << parts[4] << "\n";
      cout << "Status:\t\t" << parts[5] << "\n";
      cout << "Bytes sent:\t" << parts[6] << "\n";
      cout << "Referrer:\t" << parts[7] << "\n";
      cout << "User agent:\t" << parts[8] << "\n";
    }

    file.close();
  }
}