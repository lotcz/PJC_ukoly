#include "tiny-03.hpp"
#include <sstream>
#include <iostream>

void output_value(std::string name, double value) {
  std::cout << name;
  std::cout << ": ";
  std::cout << value;
  std::cout << "\n";
}

void output_result(statistics result) {
  output_value("min", result.min);
  output_value("max", result.max);
  output_value("median", result.median);
}

int main() {
  std::stringstream sstr;
  sstr << "3 17 32 29";
  auto summary = summarize_data(sstr);
  output_result(summary[0]);

  std::stringstream sstr2;
  sstr2 << "1 1\n"
       << "2 2 2\n"
       << "9 84 24 82 24 80 24 55 73 29";
  summary = summarize_data(sstr2);
  output_value("size", summary.size());
  output_result(summary[0]);
  output_result(summary[1]);
  output_result(summary[2]);
}
