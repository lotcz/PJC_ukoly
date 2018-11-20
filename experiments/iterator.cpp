#include <iostream>
#include "../output.cpp"

class MyIterator {
private:
  int* m_values = nullptr;
  int m_length = 0;
public:

  int* getValues() {
    return m_values;
  }

  int getLength() {
    return m_length;
  }

  int* begin() {
    return m_values;
  }

  int* end() {
    return begin()+m_length;
  }

  void add(int value) {
    int* new_arr = new int[m_length+1];
    for ( int i = 0; i < m_length; i++ ) {
      new_arr[i] = m_values[i];
    }
    new_arr[m_length] = value;
    m_length++;
    m_values = new_arr;
  }
};

int main() {
  MyIterator it;
  it.add(1);
  it.add(2);
  it.add(3);
  it.add(10);
  output_array("Values", it.getValues(), it.getLength());
  output_iterator("test", it.begin(), it.end());

}
