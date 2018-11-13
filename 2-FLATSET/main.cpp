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

    auto my_lesser = [] (int a, int b) {return a < b; };
    auto my_greater = [] (int a, int b) {return a > b; };
    std::vector<int> e{ 0,1,2,3 };
    flat_set<int, bool(*)(int, int)> l1(e.begin(), e.end(), my_lesser);
    flat_set<int, bool(*)(int, int)> l2(e.begin(), e.end(), my_greater);

    output_set("set 1", &l1);
    output_set("set 2", &l2);

    l1.swap(l2);

    output_set("set 1 swapped", &l1);
    output_set("set 2 swapped", &l2);
    /*
    l1.insert(100);
    l2.insert(-100);
    */

  } catch (std::exception e) {
    output_value("ex:", e.what());
  }
}
