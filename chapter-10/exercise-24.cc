/*
 * Exercise 10.24: Use bind and check_size to find the first element in a vector
 * of ints that has a value greater than the length of a specified string value.
 */

#include <algorithm>   // std::find_if
#include <functional>  // std::bind
#include <iostream>    // std::cout
#include <string>      // std::string
#include <vector>      // std::vector

/**
 * @brief Checks if an integer is greater than a string's length
 * @param s The string to compare against
 * @param i The integer to check
 * @return True if i > s.length()
 */
bool CheckSize(const std::string& s, int i) {
  return i > static_cast<int>(s.size());
}

/**
 * @brief Finds first int in vector greater than string's length
 * @param ivec Vector of integers to search
 * @param s Reference string for length comparison
 * @return Iterator to found element or end() if none
 */
auto FindFirstGreaterThanStringLength(const std::vector<int>& ivec,
                                      const std::string& s) {
  return std::find_if(ivec.begin(), ivec.end(),
                      std::bind(CheckSize, s, std::placeholders::_1));
}

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::string test_str = "hello";

  auto result = FindFirstGreaterThanStringLength(numbers, test_str);

  if (result != numbers.end()) {
    std::cout << "First number > '" << test_str << "' length ("
              << test_str.size() << ") is: " << *result << '\n';
  } else {
    std::cout << "No numbers > '" << test_str << "' length found\n";
  }

  // Additional test cases
  std::vector<std::pair<std::string, std::vector<int>>> test_cases = {
      {"hi", {1, 2, 3}},        //
      {"world", {1, 2, 5, 8}},  //
      {"cpp", {1, 4, 5}}};

  for (const auto& cases : test_cases) {
    auto res = FindFirstGreaterThanStringLength(cases.second, cases.first);
    std::cout << "For string '" << cases.first << "' (length "
              << cases.first.size() << "): ";
    if (res != cases.second.end()) {
      std::cout << "Found " << *res << '\n';
    } else {
      std::cout << "No match found\n";
    }
  }

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-24.cc && ./main
 * First number > 'hello' length (5) is: 6
 * For string 'hi' (length 2): Found 3
 * For string 'world' (length 5): Found 8
 * For string 'cpp' (length 3): Found 4
 */
