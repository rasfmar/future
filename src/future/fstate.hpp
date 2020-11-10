#ifndef _FSTATE
#define _FSTATE
#include <stack>
#include <string>
#include <map>
#include "internal/_ftoken.hpp"

struct fstate {
  std::map<std::string, _ftoken*> definitions;
  std::stack<_ftoken*> stack;

  fstate();
  ~fstate();
};

#endif
