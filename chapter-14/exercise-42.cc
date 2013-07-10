/*
 * Exercise 14.42: Using library function objects and adaptors, define an
 * expression to
 *     (a) Count the number of values that are greater than 1024
 *     (b) Find the first string that is not equal to pooh
 *     (c) Multiply all values by 2
 */

#include <algorithm>   // std::count_if
#include <functional>  // std::plus, std::bind
#include <iostream>    // std::cin, std::cout
#include <vector>      // std::vector

int main() {
  /*
   * TASK (a): Count the number of values greater than 1024
   *
   * Using std::greater<int> with std::bind to create a unary predicate
   * that checks if a value is greater than the constant 1024.
   */
  {
    constexpr int target_value = 1024L;
    const std::vector<int> numbers = {512, 1024, 2048, 4096, 8192, 256};

    std::greater<int> greater;
    std::cout << "(a) Values greater than " << target_value << ": "
              << std::count_if(numbers.begin(), numbers.end(),
                               std::bind(std::greater<int>(),
                                         std::placeholders::_1, target_value))
              << '\n';
  }

  /*
   * TASK (b): Find the first string not equal to "pooh"
   *
   * Using std::not_equal_to<std::string> with std::bind to create
   * a predicate that finds the first non-"pooh" string.
   */
  {
    const std::string target_string = "pooh";
    std::vector<std::string> words = {"pooh", "pooh", "tigger", "pooh",
                                      "rabbit"};

    std::cout << "(b) First string not equal to \"" << target_string << "\": "
              << *std::find_if(words.begin(), words.end(),
                               std::bind(std::not_equal_to<std::string>(),
                                         std::placeholders::_1, target_string))
              << '\n';
  }

  /*
   * TASK (c): Multiply all values by 2
   *
   * Using std::multiplies<int> with std::bind to create a function
   * that multiplies each element by 2, then using std::transform
   * to apply it to the entire sequence.
   */
  {
    constexpr int factor = 2;
    std::vector<int> values = {1, 2, 3, 4, 5};
    std::vector<int> double_values(values.size());
    std::transform(
        values.begin(), values.end(), double_values.begin(),
        std::bind(std::multiplies<int>(), std::placeholders::_1, factor));
    std::cout << "(c) Double values: ";
    for (const auto num : double_values) std::cout << num << ' ';
    std::cout << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-42.cc && ./main
 * (a) Values greater than 1024: 3
 * (b) First string not equal to "pooh": tigger
 * (c) Double values: 2 4 6 8 10
 */
