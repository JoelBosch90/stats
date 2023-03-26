#ifndef SEGMENT_TO_URL_H
#define SEGMENT_TO_URL_H

#include <string>

struct url
{
  std::string full_text;
  std::string protocol;
  std::string authentication;
  std::string domain;
  std::string port;
  std::string query;
  std::string fragment;
};

url segment_to_url(std::string segment, std::string salt);

#endif