#include <string>
#include <iostream>
#include <vector>

#include "flatset.hpp"
#include "tests-helpers.cpp"
#include "output.cpp"

template <typename T>
void output_iterator(std::string name, T start, T end) {
  output_field("name", name);
  for (auto it = start; it != end; it++) {
    output(*it);
    output(",");
  }
  output("\n");
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
    flat_set<tracker> fs;
    tracker t(1);
    auto start = tracker::cnt;
    output_field("start", start);
    fs.insert(std::move(t));
    auto t1 = tracker::cnt;
    output_field("t1   ", t1);

    //output_set("fs", &fs);
  } catch (std::exception e) {
    output_field("ex:", e.what());
  }
}
