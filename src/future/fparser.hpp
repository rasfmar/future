#ifndef _FPARSER
#define _FPARSER
#include <string>
#include <vector>
#include <sstream>
#include "internal/_ftoken.hpp"
#include "fstate.hpp"

struct fparser {
  // stringstream?
  std::stringstream input;
  std::vector<_ftoken*> tokens;

  fparser();
  ~fparser();

  void operator<<(const std::string str);
  void operator<<(const char *cstr);
  void operator<<(const char chr);
  
  void parse();
};

#endif
