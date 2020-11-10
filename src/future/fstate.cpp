#include <stack>
#include <string>
#include <map>
#include "internal/_ftoken.hpp"
#include "fstate.hpp"

fstate::fstate() {
  // should these be heap allocations?
  this->definitions = std::map<std::string, _ftoken*>();
  this->stack = std::stack<_ftoken*>();   
}

fstate::~fstate() {

}