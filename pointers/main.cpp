#include <iostream>

void out(std::string name, int value) {
  std::cout << name;
  std::cout << ": ";
  std::cout << value;
  std::cout << "\n";
}

void out(std::string name, int* value) {
  std::cout << name;
  std::cout << ": ";
  std::cout << value;
  std::cout << "\n";
}

int main() {
  int i = 10;
  out("i", i);
  out("&i - address-of i", &i);
  int* p = &i;
  out("p = &i - address-of i", p);
  out("*p - dereference", *p);

}
