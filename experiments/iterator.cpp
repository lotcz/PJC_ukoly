#include <iostream>
#include "../output.cpp"

class MySet {
private:
  int* m_values = nullptr;
  int m_length = 0;
public:

  class MyIterator {
  private:
    int* m_current = nullptr;
    MySet* m_set = nullptr;
  public:

    MyIterator(MySet* src, bool is_end) {
      m_set = src;
      if (is_end && m_set->m_values != nullptr) {
        m_current = m_set->m_values+m_set->m_length;
      } else {
        m_current = m_set->m_values;
      }
    }

    MyIterator(MySet* src) {
      MyIterator(src, false);
    }

    MyIterator operator--() {
       m_current -= 1;
       return *this;
    }

    MyIterator operator++() {
       m_current += 1;
       return *this;
    }

    MyIterator operator++(int) {
       m_current += 1;
       return *this;
    }

    int operator*() {
       return *m_current;
    }

    bool operator!=(MyIterator other) {
      return (this->m_current != other.m_current);
    }

  };

  int* getValues() {
    return m_values;
  }

  int getLength() {
    return m_length;
  }

  MyIterator begin() {
    return MyIterator(this, false);
  }

  MyIterator end() {
    return MyIterator(this, true);
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
  MySet fs;
  fs.add(1);
  fs.add(2);
  fs.add(3);
  fs.add(10);
  output_array("Values", fs.getValues(), fs.getLength());
  output_iterator("Iterator", fs.begin(), fs.end());
  output_iterator("Last", --fs.end(), fs.end());

}
