#include <iostream>

template <typename T>
void output(T value) {
  std::cout << value;
}

template <typename T>
void output(std::string name, T value) {
  output(name);
  output(": ");
  output(value);
  output("\n");
}

template <typename T>
void output_field(std::string name, T value) {
  output(name, value);
}

template <typename T>
void output_array(std::string name, T* ptr, int len) {
  output_field("Array", name);
  for ( int i = 0; i < len; i++ ) {
    output(*(ptr + i));
    output(",");
  }
  output("\n");
}

template <typename T>
void output_iterator(std::string name, T start, T end) {
  output_field("Iterator", name);
  output("Elements: ");
  for (auto it = start; it != end; it++) {
    output(*it);
    output(",");
  }
  output("\n");
}
