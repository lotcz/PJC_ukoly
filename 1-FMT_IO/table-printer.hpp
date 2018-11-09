#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

class TablePrinter {
  private:
    static void output(std::ostream& out, std::string str);
    static void output_repeat(std::ostream& out, std::string str, int count);
    static void output_cell(std::ostream& out, std::string str, int width);
    static void output_row(std::ostream& out, std::string str1, std::string str2, int col_width);
  public:
    static void print_table(std::ostream& out, const std::vector<std::string>& vec);
};
