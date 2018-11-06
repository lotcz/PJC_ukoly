#include "tiny-00.hpp"

#include <string>
#include <ostream>
#include <utility>
#include <iomanip>
#include <algorithm>

void output_result(std::string name, double value, std::ostream& out) {
  out << name;
  out << ": ";
  out << std::showpoint << std::fixed << std::setprecision(2) << value;
  out << "\n";
}

/*
 min: -23.00
 max: 5.44
 mean: 9.89
*/
void write_stats(std::vector<double> const& data, std::ostream& out) {
  double min = std::numeric_limits<double>::max();
  double max = -std::numeric_limits<double>::max();
  double sum = 0.0;
  int count = 0;

  // read inputs
  for(double value : data) {
    count++;
    sum += value;
    if (value > max) {
      max = value;
    }
    if (value < min) {
      min = value;
    }
  }

  // calculate mean
  double mean;
  if (count > 0) {
    mean = sum/count;
  } else {
    mean = 0.0;
  }

  // output
  output_result("min", min, out);
  output_result("max", max, out);
  output_result("mean", mean, out);
}
