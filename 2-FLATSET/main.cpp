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
void output_iterator(std::string name, T start, T end) {
  output_value("name", name);
  for (auto it = start; it != end; it++) {
    std::cout << *it << ",";
  }
  std::cout << "\n";
}

template <typename T, typename Comparator>
void output_set(std::string name, flat_set<T, Comparator>* fs) {
  output_iterator(name, fs->begin(), fs->end());
}

template <typename T>
flat_set<T> make_flat_set(std::vector<T> const &v) {
  return flat_set<T>(v.begin(), v.end());
}

int main() {
  try {

    flat_set<int, std::greater<int>> fs;
    std::vector<int> elems = {5, 0, 0, 1, 9, 2};
    fs.insert(elems.begin(), elems.end());
    output_value("size", fs.size());
    output_set("set", &fs); //0, 1, 2, 5, 9


  } catch (std::exception e) {
    output_value("ex:", e.what());
  }
}
