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

void output_summary(std::vector<statistics> summary) {
  int size = summary.size();
  std::cout << size;
  std::cout << " results\n";
  for (int i = 0; i < size; i++) {
    output_result(summary[i]);
  }
  std::cout << "\n";
}

int main() {
  std::stringstream sstr;
  sstr << "3 17 32 29";
  output_summary(summarize_data(sstr));

  std::stringstream sstr2;
  sstr2 << "1 1\n"
       << "2 2 2\n"
       << "9 84 24 82 24 80 24 55 73 29\n";
  output_summary(summarize_data(sstr2));

  std::stringstream sstr3;
  sstr3 << "3 22 23 24\n"
       << "4 44 55 266 22\n"
       << "3 11 22 33\n"
       << "1 11\n";
  output_summary(summarize_data(sstr3));
}
