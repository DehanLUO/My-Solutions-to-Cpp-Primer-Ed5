/*
 * Exercise 3.20: Read a set of integers into a vector. Print the sum of each
 * pair of adjacent elements. Change your program so that it prints the sum of
 * the first and last elements, followed by the sum of the second and
 * second-to-last, and so on.
 */

#include <iostream>  // std::cin, std::cout
#include <vector>    // std::vector

int main() {
  std::vector<int> vec;

  std::cout << "Enter a sequence of inters: ";

  int input;
  while (std::cin >> input) {
    vec.emplace_back(input);
  }

  auto size = vec.size();

  // Print the sum of each pair of adjacent elements
  for (decltype(size) idx = 1; idx < size; ++idx) {
    std::cout << vec[idx - 1] + vec[idx] << ' ';
  }
  std::cout << '\n';

  // Print the sum of the first and the last elements ...
  for (decltype(size) idx = 0; idx < size; ++idx) {
    std::cout << vec[idx] + vec[size - idx - 1] << ' ';
  }
  std::cout << '\n';

  return 0;
}

/*
 * $  g++ -o main exercise-20.cc && ./main
 * Enter a sequence of inters: 1 2 3 4 5 6 7 8 9 10
 * 3 5 7 9 11 13 15 17 19
 * 11 11 11 11 11 11 11 11 11 11
 */