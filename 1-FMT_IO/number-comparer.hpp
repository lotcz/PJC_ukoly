#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

class NumberComparer {
  private:
    static bool compare(std::string& str1, std::string& str2);

  public:
    static std::string max_number(std::istream& in);
};
