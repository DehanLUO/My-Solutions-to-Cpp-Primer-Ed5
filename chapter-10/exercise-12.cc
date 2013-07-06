/*
 * Exercise 10.12: Write a function named compareIsbn that compares the isbn()
 * members of two Sales_data objects. Use that function to sort a vector that
 * holds Sales_data objects.
 */

#include <algorithm>  // std::sort
#include <iostream>   // std::cin, std::cout
#include <vector>     // std::vector

#include "../chapter-07/exercise-26.h"  // Sales_data

/**
 * @brief Compares Sales_data objects by ISBN
 * @param lhs Left-hand Sales_data object
 * @param rhs Right-hand Sales_data object
 * @return True if lhs's ISBN is less than rhs's ISBN
 *
 * Demonstrates strict weak ordering requirements for sorting:
 * 1. Antisymmetric: compareIsbn(a,b) => !compareIsbn(b,a) if true
 * 2. Transitive: compareIsbn(a,b) && compareIsbn(b,c) => compareIsbn(a,c)
 * 3. Irreflexive: !compareIsbn(a,a)
 */
bool CompareIsbn(const Sales_data& lhs, const Sales_data& rhs) {
  return lhs.isbn() < rhs.isbn();
}

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
  std::sort(vec.begin(), vec.end(), CompareIsbn);

  /*
   * After sorting - show ISBN-ordered results
   */
  std::cout << "\n=== After sorting by ISBN ===\n";
  PrintSalesDataVector(vec);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-12.cc && ./main < data/book_sales
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
