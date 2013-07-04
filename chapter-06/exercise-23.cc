/*
 * Exercise 6.23: Write your own versions of each of the print functions
 * presented in this section. Call each of these functions to print i and j
 * defined as follows:
 *     int i = 0, j[2] = {0, 1};
 */

#include <iostream>  // std::cout
#include <iterator>  // std::begin, std::end

// Version 1: Print a single int
void print(const int* p) {
  if (p)  // check for null pointer
    std::cout << *p << '\n';
}

// Version 2: Print an array of ints (C-style, requires size)
void print(const int* p, size_t size) {
  for (size_t i = 0; i < size; ++i) std::cout << p[i] << ' ';
  std::cout << '\n';
}

// Version 3: Print an array using begin/end pointers
void print(const int* beg, const int* end) {
  while (beg != end) std::cout << *beg++ << ' ';
  std::cout << '\n';
}

// Version 4: Print an array using reference to array
template <size_t N>
void print(const int (&arr)[N]) {
  for (auto elem : arr) std::cout << elem << ' ';
  std::cout << '\n';
}

// Version 5: Print using modern C++ iterators
template <typename T>
void print(T begin, T end) {
  for (auto it = begin; it != end; ++it) std::cout << *it << ' ';
  std::cout << '\n';
}

int main() {
  int i = 0;
  int j[2] = {0, 1};

  // Test all versions
  std::cout << "Version 1 (single int): ";
  print(&i);

  std::cout << "Version 2 (array with size): ";
  print(j, 2);

  std::cout << "Version 3 (begin/end pointers): ";
  print(std::begin(j), std::end(j));

  std::cout << "Version 4 (array reference): ";
  print(j);

  std::cout << "Version 5 (iterators): ";
  print(std::begin(j), std::end(j));

  return 0;
}

/* $ g++ -o main chapter-06/exercise-23.cc && ./main
 * Version 1 (single int): 0
 * Version 2 (array with size): 0 1
 * Version 3 (begin/end pointers): 0 1
 * Version 4 (array reference): 0 1
 * Version 5 (iterators): 0 1
 */
