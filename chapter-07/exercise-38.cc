/*
 * Exercise 7.38: We might want to supply cin as a default argument to the
 * constructor that takes an istream&. Write the constructor declaration that
 * uses cin as a default argument.
 */

#include <iostream>  // std::cin

class ExampleClass {
  friend std::istream& read(std::istream&, ExampleClass&);

 public:
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
   * Case 1: Explicit istream
   * - Uses provided stream (could be file or other stream)
   */
  std::cout << "Enter data for explicit istream:\n";
  ExampleClass from_explicit(std::cin);

  /*
   * Case 2: Default argument
   * - Will automatically use std::cin
   * - Same effect as ExampleClass(std::cin)
   */
  std::cout << "\nEnter data for default istream:\n";
  ExampleClass from_default;

  return 0;
}

/* $ g++ -o main chapter-07/exercise-38.cc && ./main
 * Enter data for explicit istream:
 * Hello
 *
 * Enter data for default istream:
 * World
 */
