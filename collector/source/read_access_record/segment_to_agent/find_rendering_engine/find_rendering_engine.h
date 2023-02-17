#ifndef FIND_RENDERING_ENGINE_H
#define FIND_RENDERING_ENGINE_H

#include <string>

struct rendering_engine
{
  std::string name;
  std::string version;
};

rendering_engine find_rendering_engine(std::string agent);

#endif