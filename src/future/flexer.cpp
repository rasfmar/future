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

  for (_ftoken *token : tokens) {
    // if it's an operator
    if (token->type >= _FPLUS) {
      switch(token->type) {
      case _FPLUS: {
        // todo error handling
        _ftoken* second_operand = fstack.top();
        fstack.pop();
        _ftoken* first_operand = fstack.top();
        fstack.pop();

        // todo assert that second operand is of same type as first
        _27: switch (first_operand->type) {
        case _FINT32: {
          int32_t first_operand_val = *(int32_t *)first_operand->val;
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
        _ftoken* second_operand = fstack.top();
        fstack.pop();
        _ftoken* first_operand = fstack.top();
        fstack.pop();

        // todo assert that second operand is of same type as first
        _60: switch (first_operand->type) {
        case _FINT32: {
          int32_t first_operand_val = *(int32_t *)first_operand->val;
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
      default:
        break;
      }
    } else {
      fstack.push(token);
    }
  }

  tokens.clear();

  while (!fstack.empty()) {
    std::cout << (fstack.top())->str() << std::endl;
    fstack.pop();
  }
}
