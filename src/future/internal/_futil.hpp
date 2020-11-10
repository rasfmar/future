#include <string>
#include "_ftype.hpp"

std::string _ftypestr(_FTYPE type) {
  switch (type) {
  case _FINT32: return "INT32";
  case _FSTRING: return "STRING";
  case _FID: return "ID";
  case _FPLUS: return "PLUS";
  case _FMINUS: return "MINUS";
  case _FEQUALS: return "EQUALS";
  case _FNULL: default:
    return "NULL";
  }
}
