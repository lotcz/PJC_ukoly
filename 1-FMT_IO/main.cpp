#include "small1.hpp"
#include <sstream>
#include <iostream>

void output_value(std::string name, double value) {
  std::cout << name;
  std::cout << ": ";
  std::cout << value;
  std::cout << "\n";
}

int main() {
  std::stringstream str;
  std::string s =
  R"f(1 2		3 4
  5		6		7 8
  9 10 12 13
  13 14		15 33
  16 17	22	11
  )f";
  str.str(s);
  auto temp = parse_matrix(str);
  output_value("first", temp.first);
  output_value("second", temp.second);

  std::vector<std::string> vec = {"abcd", "def", "ghi", "jkl"};
  print_table(str, vec);
}
