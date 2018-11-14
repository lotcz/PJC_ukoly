template <typename T>
void output(T value) {
  std::cout << value;
}

template <typename T>
void output_field(std::string name, T value) {
  output(name);
  output(": ");
  output(value);
  output("\n");
}
