#include <string>
#include <iostream>
#include <vector>

#include "flatset.hpp"
#include "tests-helpers.cpp"
#include "../output.cpp"

template <typename T>
flat_set<T> make_flat_set(std::vector<T> const &v) {
  return flat_set<T>(v.begin(), v.end());
}

template <typename T>
void output_set(std::string name, flat_set<T>* fs) {
  output_iterator(name, fs->begin(), fs->end());
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

    flat_set<int> fs;
    fs.insert(1);
    fs.insert(5);
    fs.insert(3);
    fs.insert(5);
    fs.insert(1);
    fs.insert(4);
    output_set("after insert", &fs );
    fs.erase(1);
    fs.erase(4);
    output_set("after erase", &fs );
  } catch (std::exception e) {
    output_field("ex:", e.what());
  }
}
