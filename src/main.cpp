#include <iostream>
#include <cstdint>
#include <string>
#include "future/future.hpp"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv) {
  if (argc == 1) {
    fstate *state = new fstate();
    fparser parser = fparser();

    string input = "";
    do {
      cout << ">>> ";
      std::getline(std::cin, input);
      parser << input;
      parser.parse();
      flexer::lex(state, parser);
    } while (input != "exit");
  } else if (argc == 2) {
    cout << "file" << endl;
  } else {
    cout << "usage:" << endl
         << "\t./future FILE_NAME\tinterpret file" << endl
         << "\t./future\t\tstart future console" << endl;
  }
  return 0;
}
