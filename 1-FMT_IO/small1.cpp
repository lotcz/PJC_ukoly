#include "small1.hpp"

/**
* Načtení matice ze vstupu.
* Jen spočítá řádky a slouce matice.
*/
std::pair<int, int> parse_matrix(std::istream& in){
    int rows = 0;
    int cols = 0;
    char chr;
    char last_chr;

    while (!in.eof()) {
      in >> chr;
    }
    //std::invalid_argument
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
