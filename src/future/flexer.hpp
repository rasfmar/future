#ifndef _FLEXER
#define _FLEXER
#include "internal/_ftoken.hpp"
#include "fparser.hpp"
#include "fstate.hpp"

struct flexer {
  static void lex(fstate *state, fparser &parser);
  static void lex(fstate *state, std::vector<_ftoken*> &tokens);
};

#endif
