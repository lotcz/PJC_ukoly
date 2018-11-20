#include <iostream>

template <typename T>
void out(std::string name, T value) {
  std::cout << name;
  std::cout << ": ";
  std::cout << value;
  std::cout << "\n";
}

template <class T>
class MyClass {

private:
  T m_i;

public:

  MyClass() {

  }

  MyClass(T i) {
    m_i = i;
  }

  T get() const {
    return m_i;
  }

  void set(T i) {
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

  MyClass operator+(const T& i) {
    MyClass result;
    result.set(this->get() + i);
    return result;
  }

  MyClass operator-(const MyClass& mc) {
    MyClass<T> result;
    result.set(this->get() - mc.get());
    return result;
  }

  MyClass operator-(const T& i) {
    MyClass<T> result;
    result.set(this->get() - i);
    return result;
  }

};

MyClass<int> get_mc() {
  MyClass<int> m;
  return m;
}

int main() {
  int i = 10;
  out("i", i);
  out("&i - address-of i", &i);
  int* p = &i;
  out("p = &i - address-of i", p);
  out("*p - dereference", *p);

  MyClass<int> mc(4);
  mc.set(5);
  out("mc.get", mc.get());

  MyClass<int> mc1;
  mc1.set(2);
  MyClass<int> mc2;
  mc2.set(3);
  MyClass<int> mc3 = mc1 + get_mc();
  out("mc3.get", mc3.get());
  MyClass<double> mc4;
  MyClass<double> mc5 = MyClass<double>(0.25);
  mc4 = mc5 - 0.5;
  out("mc4.get", mc4.get());

  MyClass<int>* mcp = new MyClass<int>(8);
  MyClass<int> mcp2 = *mcp;
  out("mcp.get", mcp2.get());
}
