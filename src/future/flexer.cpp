#include <iostream>
#include <vector>
#include <string>
#include "internal/_ftoken.hpp"
#include "fstate.hpp"
#include "flexer.hpp"

void flexer::lex(fstate *state, fparser &parser) {
  lex(state, parser.tokens);
}

void flexer::lex(fstate *state, std::vector<_ftoken*> &tokens) {
  std::stack<_ftoken*> fstack;

  bool die = false;
  for (_ftoken *token : tokens) {
    // if it's an operator
    if (token->type >= _FPLUS) {
      switch(token->type) {
      case _FPLUS: {
        // todo error handling
        if (fstack.size() < 2) {
          die = true;
          break;
        }
        _ftoken* second_operand = fstack.top();
        fstack.pop();
        _ftoken* first_operand = fstack.top();
        fstack.pop();

        // todo assert that second operand is of same type as first
        _27: switch (first_operand->type) {
        case _FINT32: {
          int32_t first_operand_val = *(int32_t *)first_operand->val;
          if (second_operand->type == _FID) {
            // todo stop assuming dEFINED
            std::string second_operand_val = *(std::string *)second_operand->val;
            if (!state->definitions.count(second_operand_val)) {
              // error
              die = true;
              break;
            }
            _ftoken *definition = state->definitions[second_operand_val];
            second_operand->type = definition->type;
            second_operand->val = definition->val;
          }
          if (second_operand->type != _FINT32) {
            // error!
            fstack.push(new _ftoken());
            break;
          }
          int32_t second_operand_val = *(int32_t *)second_operand->val;
          int32_t *result = new int32_t(first_operand_val + second_operand_val);
          fstack.push(new _ftoken(result));
          // delete first_operand;
          // delete second_operand;
          break;
        }
        case _FSTRING: {
          std::string first_operand_val = *(std::string *)first_operand->val;
          std::string second_operand_val = *(std::string *)second_operand->val;
          std::string *result = new std::string(first_operand_val + second_operand_val);
          fstack.push(new _ftoken(result));
          // delete first_operand;
          // delete second_operand;
          break;
        }
        case _FID: {
          // todo stop assuming its defined
          std::string first_operand_val = *(std::string *)first_operand->val;
          if (!state->definitions.count(first_operand_val)) {
            // error
            die = true;
            break;
          }
          _ftoken *definition = state->definitions[first_operand_val];
          first_operand->type = definition->type;
          first_operand->val = definition->val;
          goto _27;
        }
        default:
          fstack.push(new _ftoken());
          break;
        }
        break;
      }
      case _FMINUS: {
        // todo error handling
        if (fstack.size() < 2) {
          die = true;
          break;
        }
        _ftoken* second_operand = fstack.top();
        fstack.pop();
        _ftoken* first_operand = fstack.top();
        fstack.pop();

        // todo assert that second operand is of same type as first
        _60: switch (first_operand->type) {
        case _FINT32: {
          int32_t first_operand_val = *(int32_t *)first_operand->val;
          if (second_operand->type == _FID) {
            // todo stop assuming dEFINED
            std::string second_operand_val = *(std::string *)second_operand->val;
            if (!state->definitions.count(second_operand_val)) {
              // error
              die = true;
              break;
            }
            _ftoken *definition = state->definitions[second_operand_val];
            second_operand->type = definition->type;
            second_operand->val = definition->val;
          }
          if (second_operand->type != _FINT32) {
            // error!
            fstack.push(new _ftoken());
            break;
          }
          int32_t second_operand_val = *(int32_t *)second_operand->val;
          int32_t *result = new int32_t(first_operand_val - second_operand_val);
          fstack.push(new _ftoken(result));
          // delete first_operand;
          // delete second_operand;
          break;
        }
        case _FID: {
          // todo stop assuming its defined
          std::string first_operand_val = *(std::string *)first_operand->val;
          if (!state->definitions.count(first_operand_val)) {
            // error
            die = true;
            break;
          }
          _ftoken *definition = state->definitions[first_operand_val];
          first_operand->type = definition->type;
          first_operand->val = definition->val;
          goto _60;
        }
        default:
          fstack.push(new _ftoken());
          break;
        }
        break;
      }
      case _FEQUALS: {
        // todo error handling for empty stack
        if (fstack.size() < 2) {
          die = true;
          break;
        }
        _ftoken* second_operand = fstack.top();
        fstack.pop();
        _ftoken* first_operand = fstack.top();
        fstack.pop();

        // todo error if first operand is not an identifier
        std::string first_operand_val = *(std::string *)first_operand->val;
        // setting this directly to second_operand could be a problem
        state->definitions[first_operand_val] = second_operand->clone();
        // delete first_operand;
        // delete second_operand;
        break;
      }
      case _FPRINT: {
        if (fstack.size() < 1) {
          die = true;
          break;
        }
        _ftoken* first_operand = fstack.top();
        fstack.pop();
        if (first_operand->type == _FID) {
          std::string first_operand_val = *(std::string *)first_operand->val;
          if (!state->definitions.count(first_operand_val)) {
            die = true;
            break;
          }
          _ftoken *definition = state->definitions[first_operand_val];
          first_operand->type = definition->type;
          first_operand->val = definition->val;
        }
        std::cout << first_operand->valstr() << std::endl;
        break;
      }
      case _FINPUT: {
        std::string *in = new std::string("");
        std::getline(std::cin, *in);
        _ftoken *token = new _ftoken(in);
        fstack.push(token);
        break;
      }
      default:
        break;
      }
    } else {
      fstack.push(token);
    }

    if (die)
      break;
  }

  tokens.clear();

  while (!fstack.empty()) {
    std::cout << (fstack.top())->str() << std::endl;
    fstack.pop();
  }
}
