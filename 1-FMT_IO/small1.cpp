#include "small1.hpp"
#include <iostream>
#include <stdexcept>

bool is_whitespace(char chr) {
  return (chr == ' ' || chr == '\t');
}

bool is_newline(char chr) {
  return (chr == '\n');
}

/**
* Načtení matice ze vstupu.
* Jen spočítá řádky a slouce matice.
*/
std::pair<int, int> parse_matrix(std::istream& in) {
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

/**
* Výpis tabulky na výstup
*/
void print_table(std::ostream& out, const std::vector<std::string>& vec) {

}

/**
* Verifikace formátovaného vstupu
*/
bool validate_line(const std::string& str) {
    return true;
}

/**
* Porovnání dlouhých čísel
*/
std::string max_number(std::istream& in) {
    return {};
}
