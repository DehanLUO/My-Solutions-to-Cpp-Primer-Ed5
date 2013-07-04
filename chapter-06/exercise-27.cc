/*
 * Exercise 6.27: Write a function that takes an initializer_list<int> and
 * produces the sum of the elements in the list.
 */

#include <initializer_list>  // std::initializer_list
#include <iostream>          // std::cout

/**
 * @brief Calculates the sum of integers in an initializer_list
 * @param il List of integers to sum
 * @return int Sum of all elements
 *
 * Uses range-based for loop to iterate through elements
 * Returns 0 for empty lists
 */
int sum_ilist(std::initializer_list<int> il) {
  int sum = 0;
  for (const auto& elem : il) {  // const reference avoids copying
    sum += elem;
  }
  return sum;
}

/*
 * Alternative version using iterators explicitly
 * Demonstrates underlying implementation
 */
int sum_ilist_iter(std::initializer_list<int> il) {
  int sum = 0;
  for (auto it = il.begin(); it != il.end(); ++it) {
    sum += *it;
  }
  return sum;
}

int main() {
  // Test cases
  std::cout << "Sum 1: " << sum_ilist({1, 2, 3, 4}) << '\n';  // 10
  std::cout << "Sum 2: " << sum_ilist({-1, 0, 1}) << '\n';    // 0
  std::cout << "Sum 3: " << sum_ilist({}) << '\n';            // 0
  std::cout << "Sum 4: " << sum_ilist_iter({5}) << '\n';      // 5
  std::cout << "Sum 5: " << sum_ilist_iter({10, 20, 30, 40, 50})
            << '\n';  // 150

  return 0;
}

/* $ g++ -o main chapter-06/exercise-27.cc && ./main
 * Sum 1: 10
 * Sum 2: 0
 * Sum 3: 0
 * Sum 4: 5
 * Sum 5: 150
 */
