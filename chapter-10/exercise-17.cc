/*
 * Exercise 10.17: Rewrite exercise 10.12 from § 10.3.1 (p. 387) to use a lambda
 * in the call to sort instead of the compareIsbn function.
 */

#include <algorithm>  // std::sort
#include <iostream>   // std::cin, std::cout
#include <vector>     // std::vector

#include "../chapter-07/exercise-26.h"  // Sales_data

/**
 * @brief Prints a vector of Sales_data objects
 * @param vec The vector to print
 */
void PrintSalesDataVector(const std::vector<Sales_data>& vec) {
  for (const auto& item : vec) {
    print(std::cout, item) << '\n';
  }
}

int main() {
  std::vector<Sales_data> vec;
  Sales_data item;

  // Read input until EOF or error
  while (read(std::cin, item)) {
    vec.push_back(item);
  }

  /*
   * Before sorting - show original input order
   */
  std::cout << "=== Before sorting ===\n";
  PrintSalesDataVector(vec);

  /*
   * Sort using custom ISBN comparison
   * std::sort guarantees O(n log n) complexity
   */
  std::sort(vec.begin(), vec.end(),
            [](const Sales_data& lhs, const Sales_data& rhs) -> bool {
              return lhs.isbn() < rhs.isbn();
            });

  /*
   * After sorting - show ISBN-ordered results
   */
  std::cout << "\n=== After sorting by ISBN ===\n";
  PrintSalesDataVector(vec);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-17.cc && ./main
 * === Before sorting ===
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 2 30 15
 * 0-201-88954-4 5 60 12
 * 0-201-88954-4 7 84 12
 * 0-201-88954-4 2 24 12
 * 0-399-82477-1 2 90.78 45.39
 * 0-399-82477-1 3 136.17 45.39
 * 0-201-78345-X 3 60 20
 * 0-201-78345-X 2 50 25
 *
 * === After sorting by ISBN ===
 * 0-201-70353-X 4 99.96 24.99
 * 0-201-78345-X 3 60 20
 * 0-201-78345-X 2 50 25
 * 0-201-82470-1 4 181.56 45.39
 * 0-201-88954-4 2 30 15
 * 0-201-88954-4 5 60 12
 * 0-201-88954-4 7 84 12
 * 0-201-88954-4 2 24 12
 * 0-399-82477-1 2 90.78 45.39
 * 0-399-82477-1 3 136.17 45.39
 */
