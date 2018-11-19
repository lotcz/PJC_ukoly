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


class MyKey {
    friend struct MyKeyComparator;
    int i;
    static unsigned s_nconstructs;
    operator int() const {return i;}
public:
    static unsigned nconstructs() {return s_nconstructs;}

    explicit MyKey(int i = 0) : i(i) {s_nconstructs++;}
    MyKey(const MyKey &o) : i(o.i) {s_nconstructs++;}
    MyKey& operator=(const MyKey &o) {i = o.i; s_nconstructs++; return *this;}
    MyKey(MyKey &&o) = default;
    MyKey& operator=(MyKey &&o) = default;
};


struct MyKeyComparator {
    bool operator()(MyKey const &a, MyKey const &b) const {
      return a.i < b.i;
    }
};

unsigned MyKey::s_nconstructs = 0;

int main() {
  try {

    flat_set<tracker> fs;
    tracker t(1);
    auto start = tracker::cnt;
    fs.insert(std::move(t));
    auto t1 = tracker::cnt;
    output_field("after insert", t1 );

  } catch (std::exception e) {
    output_field("ex:", e.what());
  }
}
