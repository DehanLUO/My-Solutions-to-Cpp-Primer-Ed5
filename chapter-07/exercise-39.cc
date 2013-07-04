/*
 * Exercise 7.39: Would it be legal for both the constructor that takes a string
 * and the one that takes an istream& to have default arguments? If not, why
 * not?
 */

#include <iostream>  // std::cin, std::cout
#include <string>    // std::string

class ExampleClass {
  friend std::istream& read(std::istream&, ExampleClass&);

 public:
  /**
   * @brief Constructs with optional string parameter
   * @param str string (defaults to empty string)
   */
  explicit ExampleClass(const std::string& str = "") : member_variable(str) {}

  /**
   * @brief Constructs from input stream with cin as default
   * @param input_stream Input stream (defaults to std::cin)
   * @post Members initialized by read() operation
   */
  explicit ExampleClass(std::istream& input_stream = std::cin) {
    read(input_stream, *this);
  }

 private:
  std::string member_variable;
};

std::istream& read(std::istream& input_stream, ExampleClass& item) {
  return input_stream >> item.member_variable;
}

int main() {
  /*
   * This declaration would be ambiguous:
   * Sales_data item;
   *
   * Compiler cannot choose between:
   * 1. Sales_data(const string& = "")
   * 2. Sales_data(istream& = cin)
   */
  // ExampleClass ambiguous_item;

  return 0;
}

/* $ g++ -o main chapter-07/exercise-39.cc && ./main

 */
