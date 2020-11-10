#include <cstdint>
#include <string>
#include <sstream>
#include "_ftoken.hpp"
#include "_ftype.hpp"
#include "_fconst.hpp"
#include "_futil.hpp"

_ftoken::_ftoken(_FTYPE type, void *val) {
  this->type = type;
  this->val = val;
}

_ftoken::_ftoken(_FTYPE type) {
  void *val = nullptr;
  switch (type) {
  case _FINT32:
    val = (void *)(new int32_t(_FINT32_DEFAULT));
    break;
  case _FSTRING:
    val = (void *)(new std::string(_FSTRING_DEFAULT));
    break;
  // case _FID:?
  default:
    break;
  }
  this->type = type;
  this->val = val;
}

_ftoken::_ftoken(int32_t *val) : _ftoken(_FINT32, (void *)val) {}
_ftoken::_ftoken(std::string *val) : _ftoken(_FSTRING, (void *)val) {}
_ftoken::_ftoken() : _ftoken(_FNULL) {}
_ftoken::~_ftoken() {
  delete val;
}

std::string _ftoken::valstr() {
  switch (this->type) {
  case _FINT32: {
    int32_t pointed_int32 = *(int32_t *)this->val;
    return std::to_string(pointed_int32);
  }
  case _FSTRING: case _FID: {
    std::string pointed_string = *(std::string *)this->val;
    return pointed_string;
  }
  case _FNULL: default:
    return "";
  }
}

std::string _ftoken::str() {
  std::string typestr = _ftypestr(this->type);
  std::string valstr = this->valstr();
  auto finalstr = std::stringstream();
  finalstr << typestr << _FTOKEN_STR_DELIMETER
           << _FTOKEN_STR_LEFT << valstr
           << _FTOKEN_STR_RIGHT;
  return finalstr.str();
}

_ftoken *_ftoken::clone() {
  _ftoken *token = new _ftoken(this->type, this->val);
  return token;
}
