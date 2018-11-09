#include "small1.hpp"
#include "matrix-parser.hpp"
#include "table-printer.hpp"

/**
* Načtení matice ze vstupu.
* Jen spočítá řádky a slouce matice.
*/
std::pair<int, int> parse_matrix(std::istream& in) {
  return MatrixParser::parse_matrix(in);
}

/**
* Výpis tabulky na výstup
*/
void print_table(std::ostream& out, const std::vector<std::string>& vec) {
  return TablePrinter::print_table(out, vec);
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
