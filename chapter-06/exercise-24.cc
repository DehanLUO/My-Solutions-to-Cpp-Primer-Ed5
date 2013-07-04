/*
 * Exercise 6.24: Explain the behavior of the following function. If there are
 * problems in the code, explain what they are and how you might fix them.
 *     void print(const int ia[10]) {
 *       for (size_t i = 0; i != 10; ++i)
 *         cout << ia[i] << endl;
 *       }
 */

#include <iostream>  // std::cout
#include <iterator>  // std::begin, std::end

/**
 * Problematic function:
 * void print(const int ia[10]) {
 *   for (size_t i = 0; i != 10; ++i)
 *     cout << ia[i] << endl;
 * }
 *
 * Issues:
 * 1. The [10] is misleading - it's treated as int* by compiler
 * 2. No size safety - can be called with arrays of any size
 * 3. Hardcoded size creates potential buffer overflows
 */

// Fixed version 1: Using array reference (size checked at compile time)
template <size_t N>
void print_safe(const int (&ia)[N]) {
  for (auto elem : ia) std::cout << elem << ' ';
}

// Fixed version 2: Explicit size parameter
void print_safe(const int* ia, size_t size) {
  for (size_t i = 0; i < size; ++i) std::cout << ia[i] << ' ';
}

// Fixed version 3: Using iterators (most flexible)
void print_safe(const int* begin, const int* end) {
  while (begin != end) std::cout << *begin++ << ' ';
}

int main() {
  int good[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int small[5] = {0, 1, 2, 3, 4};

  // Original dangerous function would accept both:
  // print(good);  // OK but misleading
  // print(small); // Buffer overflow!

  // Safe versions:
  std::cout << "Version 1 (array reference):\n";
  print_safe(good);  // OK - size checked

  std::cout << "\nVersion 2 (size parameter):\n";
  print_safe(small, 5);  // Correct size passed

  std::cout << "\nVersion 3 (iterators):\n";
  print_safe(std::begin(good), std::end(good));

  return 0;
}

/* $ g++ -o main chapter-06/exercise-24.cc && ./main
 * Version 1 (array reference):
 * 0 1 2 3 4 5 6 7 8 9
 * Version 2 (size parameter):
 * 0 1 2 3 4
 * Version 3 (iterators):
 * 0 1 2 3 4 5 6 7 8 9
 */
