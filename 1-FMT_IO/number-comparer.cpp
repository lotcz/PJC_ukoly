#include "number-comparer.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

/**
* return true if str1 is bigger than str2.
*/
bool NumberComparer::compare(std::string& str1, std::string& str2) {
  if (str1.length() > str2.length()) {
    return true;
  } else if (str1.length() < str2.length()) {
    return false;
  } else {
    return (str1 > str2);
  }
}

std::string NumberComparer::max_number(std::istream& in) {
  std::string max = "";
  std::string str = "";
  char chr;

  while (in.get(chr)) {
    if (chr == ',') {
      if (compare(str, max)) {
        max = str;
      }
      str = "";
    } else {
      str += chr;
    }
  }

  if (compare(str, max)) {
    max = str;
  }

  return max;
}
