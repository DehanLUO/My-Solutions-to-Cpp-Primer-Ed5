/*
 * Exercise 9.18: Write a program to read a sequence of strings from the
 * standard input into a deque. Use iterators to write a loop to print the
 * elements in the deque.
 */

#include <deque>     // std::deque
#include <iostream>  // std::cin, std::cout, std::getline
#include <iterator>  // std::ostream_iterator
#include <string>    // std::string

/**
 * @brief Reads strings from stdin into a deque until EOF
 * @param deque The reference to store the input string
 */
void ReadStringsToDeque(std::deque<std::string>& deque) {
  std::string current_string;

  /*
   * Read until EOF (Ctrl+D on Unix, Ctrl+Z on Windows)
   * Using getline to preserve whitespace within strings
   */
  while (std::getline(std::cin, current_string)) {
    deque.push_back(current_string);
  }
}

/**
 * @brief Prints deque contents using iterators
 * @param deque The deque to print
 *
 * Demonstrates three iterator-based printing methods:
 * 1. Traditional iterator loop
 * 2. Range-based for loop
 * 3. STL copy algorithm with ostream_iterator
 */
void PrintDeque(const std::deque<std::string>& deque) {
  /*
   * Method 1: Traditional iterator loop
   * Shows explicit iterator declaration and increment
   */
  std::cout << "Method 1 (traditional):\n";
  for (auto it = deque.begin(); it != deque.end(); ++it) {
    std::cout << *it << '\n';
  }

  /*
   * Method 2: Range-based for loop
   * Cleaner syntax when iterator details aren't needed
   */
  std::cout << "\nMethod 2 (range-based):\n";
  for (const auto& str : deque) {
    std::cout << str << '\n';
  }

  /*
   * Method 3: STL copy algorithm
   * Most concise, demonstrates STL algorithm usage
   */
  std::cout << "\nMethod 3 (STL algorithm):\n";
  std::copy(deque.begin(), deque.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
}

int main() {
  /*
   * Main execution flow:
   * 1. Read input strings into deque
   * 2. Print deque contents using iterators
   */
  std::cout << "Enter strings (EOF to end input):\n";
  std::deque<std::string> string_deque;
  ReadStringsToDeque(string_deque);

  std::cout << "\nDeque contents:\n";
  PrintDeque(string_deque);

  return 0;
}
/*
 * $ g++ -o main chapter-09/exercise-18.cc && ./main < data/book_sales
 * Enter strings (EOF to end input):
 *
 * Deque contents:
 * Method 1 (traditional):
 * 0-201-70353-X 4 24.99
 * 0-201-82470-1 4 45.39
 * 0-201-88954-4 2 15.00
 * 0-201-88954-4 5 12.00
 * 0-201-88954-4 7 12.00
 * 0-201-88954-4 2 12.00
 * 0-399-82477-1 2 45.39
 * 0-399-82477-1 3 45.39
 * 0-201-78345-X 3 20.00
 * 0-201-78345-X 2 25.00
 *
 * Method 2 (range-based):
 * 0-201-70353-X 4 24.99
 * 0-201-82470-1 4 45.39
 * 0-201-88954-4 2 15.00
 * 0-201-88954-4 5 12.00
 * 0-201-88954-4 7 12.00
 * 0-201-88954-4 2 12.00
 * 0-399-82477-1 2 45.39
 * 0-399-82477-1 3 45.39
 * 0-201-78345-X 3 20.00
 * 0-201-78345-X 2 25.00
 *
 * Method 3 (STL algorithm):
 * 0-201-70353-X 4 24.99
 * 0-201-82470-1 4 45.39
 * 0-201-88954-4 2 15.00
 * 0-201-88954-4 5 12.00
 * 0-201-88954-4 7 12.00
 * 0-201-88954-4 2 12.00
 * 0-399-82477-1 2 45.39
 * 0-399-82477-1 3 45.39
 * 0-201-78345-X 3 20.00
 * 0-201-78345-X 2 25.00
 */
