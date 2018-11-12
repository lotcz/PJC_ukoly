#include "flatset.hpp"
#include <string>
#include <iostream>
#include <vector>

template <typename T>
void output_value(std::string name, T value) {
  std::cout << name;
  std::cout << ": ";
  std::cout << value;
  std::cout << "\n";
}

template <typename T>
flat_set<T> make_flat_set(std::vector<T> const &v) {
  return flat_set<T>(v.begin(), v.end());
}

int main() {
  auto l = make_flat_set<int>({ 1, 4, 8, 2, 3, 12, 4, 5, 12, -1 });
  output_value("test const empty", l.empty());
  output_value("test const size", l.size());
  for (auto it = l.begin(); it != l.end(); ++it) {
    std::cout << *it << ",";
  }
}
