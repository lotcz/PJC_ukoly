#include "matrix-parser.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

bool MatrixParser::is_whitespace(char chr) {
  return (chr == ' ' || chr == '\t');
}

bool MatrixParser::is_newline(char chr) {
  return (chr == '\n');
}

std::pair<int, int> MatrixParser::parse_matrix(std::istream& in) {
  int rows = 0;
  int cols = 0;

  char chr; // current character
  char last_chr; // previous character
  int row_cols = 0; //columns in current row

  while (in.get(chr)) {
    if (is_whitespace(chr)) {
      if (!is_whitespace(last_chr) && !is_newline(last_chr)) {
        row_cols++;
      }
    } else if (is_newline(chr)) {
      row_cols++;
      rows++;
      if (cols == 0) {
        cols = row_cols;
      } else if (cols != row_cols) {
        throw std::invalid_argument("Rows are not of the same size!");
      }
      row_cols = 0;
    }
    last_chr = chr;
  }
  return std::make_pair(rows, cols);
}
