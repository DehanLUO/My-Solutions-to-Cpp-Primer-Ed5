/*
 * Exercise 8.2: Test your function by calling it, passing cin as an argument.
 */

#include "exercise-01.h"  // ProcessInputStream

int main() {
  std::cout << "Enter text (Ctrl+D/Z to end):\n";
  ProcessInputStream<std::string>(std::cin);

  return 0;
}

/*
 * $ g++ -o main chapter08/exercise-02.cc && ./main < data/book_sales
 * Enter text (Ctrl+D/Z to end):
 * 0-201-70353-X 4 24.99 0-201-82470-1 4 45.39 0-201-88954-4 2 15.00 0-201-88954-4 5 12.00 0-201-88954-4 7 12.00 0-201-88954-4 2 12.00 0-399-82477-1 2 45.39 0-399-82477-1 3 45.39 0-201-78345-X 3 20.00 0-201-78345-X 2 25.00 [Illegal input: ""]
 */
 