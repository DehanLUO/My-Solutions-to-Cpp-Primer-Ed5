/*
 * Exercise 9.19: Rewrite the program from the previous exercise to use a list.
 * List the changes you needed to make.
 */

#include <iostream>  // std::cin, std::cout, std::getline
#include <iterator>  // std::ostream_iterator
#include <list>      // std::list
#include <string>    // std::string

/**
 * @brief Reads strings from stdin into a list until EOF
 * @param list The list to store
 *
 * Changes from deque version:
 * - Param type changed from deque to list
 */
void ReadStringsToList(std::list<std::string>& list) {
  std::string current_string;

  while (std::getline(std::cin, current_string)) {
    list.push_back(current_string);
  }
}

/**
 * @brief Prints list contents using iterators
 * @param list The list to print
 *
 * Changes from deque version:
 * - Parameter type changed from deque to list
 * - All iterator operations remain identical
 */
void PrintList(const std::list<std::string>& list) {
  /* Method 1: Traditional iterator loop */
  std::cout << "Method 1 (traditional):\n";
  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << '\n';
  }

  /* Method 2: Range-based for loop */
  std::cout << "\nMethod 2 (range-based):\n";
  for (const auto& str : list) {
    std::cout << str << '\n';
  }

  /* Method 3: STL copy algorithm */
  std::cout << "\nMethod 3 (STL algorithm):\n";
  std::copy(list.begin(), list.end(),
            std::ostream_iterator<std::string>(std::cout, "\n"));
}

int main() {
  std::cout << "Enter strings (EOF to end input):\n";
  std::list<std::string> string_list;
  ReadStringsToList(string_list);

  std::cout << "\nList contents:\n";
  PrintList(string_list);

  return 0;
}
/*
 * $ g++ -o main chapter-09/exercise-19.cc && ./main < data/book_sales
 * Enter strings (EOF to end input):
 *
 * List contents:
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
