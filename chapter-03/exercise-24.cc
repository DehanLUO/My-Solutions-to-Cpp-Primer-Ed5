/*
 * Exercise 3.24: Redo the last exercise from § 3.3.3 (p. 105) using iterators.
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
  for (auto it = vec.begin(); it + 1 != vec.end(); ++it) {
    std::cout << *it + *(it + 1) << ' ';
  }
  std::cout << '\n';

  // Print the sum of the first and the last elements ...
  for (auto it_front = vec.begin(), it_back = vec.end() - 1;
       it_front != vec.end(); ++it_front, --it_back) {
    std::cout << *it_front + *it_back << ' ';
  }
  std::cout << '\n';

  return 0;  // Successful execution
}

/*
 * $  g++ -o main exercise-24.cc && ./main
 * Enter a sequence of inters: 1 2 3 4 5 6 7 8 9 10
 * 3 5 7 9 11 13 15 17 19
 * 11 11 11 11 11 11 11 11 11 11
 */