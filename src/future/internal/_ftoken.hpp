#ifndef __FTOKEN
#define __FTOKEN
#include "_ftype.hpp"
#include <cstdint>
#include <string>

struct _ftoken {
  _FTYPE type;
  void *val;

  _ftoken(_FTYPE type, void *val);
  _ftoken(_FTYPE type);
  _ftoken(int32_t *val);
  _ftoken(std::string *val);
  _ftoken();
  ~_ftoken();

  std::string valstr();
  std::string str();

  _ftoken *clone();
};

#endif
