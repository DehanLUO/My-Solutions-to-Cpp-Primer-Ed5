/*
 * Exercise 14.43: Using library function objects, determine whether a given int
 * value is divisible by any element in a container of ints.
 */

#include <algorithm>   // std::count_if
#include <functional>  // std::bind, std::modulus
#include <iostream>    // std::cout
#include <vector>      // std::vector

/**
 * @brief Checks if dividend is divisible by any divisor in container using
 * nested binds for pure library solution
 * @param divisors Container of potential divisors
 * @param dividend Number to check for divisibility
 * @return bool True if dividend is divisible by any divisor, false otherwise
 * @time Complexity O(n) where n is number of divisors
 * @space Complexity O(1) no additional space required
 *
 * This version uses only library function objects without lambdas,
 * but is less readable and still requires zero divisor handling.
 */
bool IsDivisibleByAll(const std::vector<int>& divisors, int dividend) {
  return std::count_if(divisors.begin(), divisors.end(),
                       std::bind(std::modulus<int>(), dividend,
                                 std::placeholders::_1)) == 0;
}

int main() {
  const std::vector<int> test_divisors = {2, 3, 5, 7, 11};

  {
    int test_dividend = 30;
    bool result = IsDivisibleByAll(test_divisors, test_dividend);
    std::cout << test_dividend << " divisible by any of {2, 3, 5, 7, 11}: "  //
              << (result ? "true" : "false") << '\n';
  }

  {
    int test_dividend = 0;
    bool result = IsDivisibleByAll(test_divisors, test_dividend);
    std::cout << test_dividend << " divisible by any of {2, 3, 5, 7, 11}: "  //
              << (result ? "true" : "false") << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-43.cc && ./main
 * 30 divisible by any of {2, 3, 5, 7, 11}: false
 * 0 divisible by any of {2, 3, 5, 7, 11}: true
 */
