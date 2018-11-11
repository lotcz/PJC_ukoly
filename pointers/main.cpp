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

class MyClass {

private:
  int m_i;

public:

  MyClass() {

  }

  MyClass(int i) {
    m_i = i;
  }

  int get() const {
    return m_i;
  }

  void set(int i) {
    m_i = i;
  }

  MyClass operator+(const MyClass& mc) {
    MyClass result;
    result.set(this->get() + mc.get());
    return result;
  }

  MyClass operator+(const MyClass&& mc) {
    MyClass result;
    result.set(17);
    return result;
  }

  MyClass operator+(const int& i) {
    MyClass result;
    result.set(this->get() + i);
    return result;
  }

  MyClass operator-(const MyClass& mc) {
    MyClass result;
    result.set(this->get() - mc.get());
    return result;
  }

};

MyClass get_mc() {
  MyClass m;
  return m;
}

int main() {
  int i = 10;
  out("i", i);
  out("&i - address-of i", &i);
  int* p = &i;
  out("p = &i - address-of i", p);
  out("*p - dereference", *p);

  MyClass mc(4);
  mc.set(5);
  out("mc.get", mc.get());

  MyClass mc1;
  mc1.set(2);
  MyClass mc2;
  mc2.set(3);
  MyClass mc3 = mc1 + get_mc();
  out("mc3.get", mc3.get());
  MyClass mc4 = mc1 - mc2;
  out("mc4.get", mc4.get());

  MyClass* mcp = new MyClass(8);
  MyClass mcp2 = *mcp;
  out("mcp.get", mcp2.get());
}
