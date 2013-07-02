/*
 * Exercise 4.27: What is the result of each of these expressions?
 *     unsigned long ul1 = 3, ul2 = 7;
 *     (a) ul1 & ul2
 *     (b) ul1 | ul2
 *     (c) ul1 && ul2
 *     (d) ul1 || ul2
 */

#include <bitset>    // std::bitset
#include <iostream>  // std::cout

/**
 * @brief Demonstrates bitwise and logical operations
 */
void ExplainOperations() {
  unsigned long ul1 = 3;  // Binary: 0011
  unsigned long ul2 = 7;  // Binary: 0111

  // (a) Bitwise AND
  std::cout << "(a) ul1 & ul2:\n";
  std::cout << "ul1:    " << std::bitset<4>(ul1) << "\n";
  std::cout << "ul2:    " << std::bitset<4>(ul2) << "\n";
  std::cout << "Result: " << std::bitset<4>(ul1 & ul2)
            << " (decimal: " << (ul1 & ul2) << ")\n\n";

  // (b) Bitwise OR
  std::cout << "(b) ul1 | ul2:\n";
  std::cout << "ul1:    " << std::bitset<4>(ul1) << "\n";
  std::cout << "ul2:    " << std::bitset<4>(ul2) << "\n";
  std::cout << "Result: " << std::bitset<4>(ul1 | ul2)
            << " (decimal: " << (ul1 | ul2) << ")\n\n";

  // (c) Logical AND
  std::cout << "(c) ul1 && ul2:\n";
  std::cout << "ul1 as bool: " << (ul1 != 0) << "\n";
  std::cout << "ul2 as bool: " << (ul2 != 0) << "\n";
  std::cout << "Result:      " << (ul1 && ul2) << " (boolean)\n\n";

  // (d) Logical OR
  std::cout << "(d) ul1 || ul2:\n";
  std::cout << "ul1 as bool: " << (ul1 != 0) << "\n";
  std::cout << "ul2 as bool: " << (ul2 != 0) << "\n";
  std::cout << "Result:      " << (ul1 || ul2) << " (boolean)\n";
}

int main() {
  ExplainOperations();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-17.cc && ./main
 * (a) ul1 & ul2:
 * ul1:    0011
 * ul2:    0111
 * Result: 0011 (decimal: 3)
 *
 * (b) ul1 | ul2:
 * ul1:    0011
 * ul2:    0111
 * Result: 0111 (decimal: 7)
 *
 * (c) ul1 && ul2:
 * ul1 as bool: 1
 * ul2 as bool: 1
 * Result:      1 (boolean)
 *
 * (d) ul1 || ul2:
 * ul1 as bool: 1
 * ul2 as bool: 1
 * Result:      1 (boolean)
 */
