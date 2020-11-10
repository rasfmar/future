#ifndef _FPARSE
#define _FPARSE
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "internal/_ftoken.hpp"
#include "internal/_fconst.hpp"
#include "fparser.hpp"

fparser::fparser() {
  this->input = std::stringstream();
  this->tokens = std::vector<_ftoken*>();
}

fparser::~fparser() {

}

void fparser::operator<<(const std::string str) {
  this->input << str;
}

void fparser::operator<<(const char *cstr) {
  this->input << cstr;
}

void fparser::operator<<(const char chr) {
  this->input << chr;
}

void fparser::parse() {
  // eof
  this->input << '\0';

  std::string src = this->input.str();
  bool string_flag = false;
  bool int_flag = false;
  bool id_flag = false;
  auto token_builder = std::stringstream();

  for(size_t char_index = 0; char_index < src.length(); char_index++) {
    char chr = src[char_index];
    if (string_flag) {
      if ((chr == '"' || chr == '\'') || (_FDEBUG && chr == '\0')) {
        // build,
        std::string *str = new std::string(token_builder.str());
        _ftoken *fstr = new _ftoken(str);
        this->tokens.push_back(fstr);
        token_builder.str("");
        string_flag = false;
        // don't goto begin so that we skip over quote
        // goto begin;
      } else {
        token_builder << chr;
      }
    } else if (int_flag) {
      if (!isdigit(chr) || (_FDEBUG && chr == '\0')) {
        int32_t *int32 = new int32_t(std::stoi(token_builder.str()));
        _ftoken *fint32 = new _ftoken(int32);
        this->tokens.push_back(fint32);
        token_builder.str("");
        int_flag = false;
        char_index--;
      } else {
        token_builder << chr;
      }
    } else if (id_flag) {
      if (!isalnum(chr) || (_FDEBUG && chr == '\0')) {
        std::string *id = new std::string(token_builder.str());
        _ftoken *fid = new _ftoken(_FID, id);
        this->tokens.push_back(fid);
        token_builder.str("");
        id_flag = false;
        char_index--;
      } else {
        token_builder << chr;
      }
    } else {
      if (chr == '\0') {
        break;
      } else if (chr == '+') {
        _ftoken *fplus = new _ftoken(_FPLUS);
        this->tokens.push_back(fplus);
        // might be unnecessary
        token_builder.str("");
      } else if (chr == '-') {
        _ftoken *fminus = new _ftoken(_FMINUS);
        this->tokens.push_back(fminus);
        token_builder.str("");
      } else if (chr == '=') {
        _ftoken *fequals = new _ftoken(_FEQUALS);
        this->tokens.push_back(fequals);
        token_builder.str("");
      } else if (chr == '"' || chr == '\'') {
        string_flag = true;
        // don't include quote
        // token_builder << chr;
      } else if (isdigit(chr)) {
        int_flag = true;
        token_builder << chr;
      } else if (chr != ' ') {
        id_flag = true;
        token_builder << chr;
      }
    }
  }

  this->input.str("");
  // lexer will do this
  // this->tokens.clear();
}

#endif
