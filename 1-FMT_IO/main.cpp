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
  output_value("validation", validate_line("false 07 7 G"));  
}
