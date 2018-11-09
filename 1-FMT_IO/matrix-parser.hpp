#include <iostream>
#include <sstream>

class MatrixParser {
  private:
    static bool is_whitespace(char chr);
    static bool is_newline(char chr);
  public:
    static std::pair<int, int> parse_matrix(std::istream& in);
};
