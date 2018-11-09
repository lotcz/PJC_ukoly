#include "table-printer.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

void TablePrinter::output(std::ostream& out, std::string str) {
  out << str;
}

void TablePrinter::output_repeat(std::ostream& out, std::string str, int count) {
  for (int i = 0; i < count; i++) {
    output(out, str);
  }
}

void TablePrinter::output_cell(std::ostream& out, std::string str, int width) {
  output_repeat(out, " ", width - str.length());
  output(out, str);
}

void TablePrinter::output_row(std::ostream& out, std::string str1, std::string str2, int col_width) {
  output(out, "|");
  output_cell(out, str1, col_width);
  output(out, "|");
  output_cell(out, str2, col_width);
  output(out, "|");
  output(out, "\n");
}

void TablePrinter::print_table(std::ostream& out, const std::vector<std::string>& vec) {
  int col_width = 0;
  int len = 0;

  for (std::string str : vec) {
    len = str.length() ;
    if (len > col_width) {
      col_width = len;
    }
  }
  col_width += 1;
  int table_width = 1 + col_width + 1 + col_width + 1;

  output_repeat(out, "-", table_width);output(out, "\n");

  std::string* col1 = nullptr;

  for (std::string str : vec) {
    if (col1 == nullptr) {
      std::string s = str;
      col1 = &s;
    } else {
      output_row(out, *col1, str, col_width);
      col1 = nullptr;
    }
  }
  if (col1 != nullptr) {
    output_row(out, *col1, " ", col_width);
  }
  output_repeat(out, "-", table_width);output(out, "\n");
}
