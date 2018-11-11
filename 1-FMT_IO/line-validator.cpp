#include "line-validator.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

bool LineValidator::validate_line(const std::string& str) {
  std::stringstream sstr;
  sstr.str(str);
  bool b;
  if (sstr >> std::boolalpha >> b) {
    int oct;
    if (sstr >> std::oct >> oct) {
      int dec;
      if (!(sstr >> std::dec >> dec)) {
        return false;
      }
      int hex;
      if (!(sstr >> std::hex >> hex)) {
        return false;
      }
      if (!sstr.eof()) {
        return false;
      }
      return (b == ((dec == hex) && (hex == oct)));
    } else {
      return false;
    }
  } else {
    return false;
  }
}
