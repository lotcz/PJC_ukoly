#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

class LineValidator {
  private:
    //static void output(std::ostream& out, std::string str);

  public:
    static bool validate_line(const std::string& str);
};
