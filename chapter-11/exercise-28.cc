/*
 * Exercise 11.28: Define and initialize a variable to hold the result of
 * calling find on a map from string to vector of int.
 */

#include <map>     // std::map
#include <string>  // std::string
#include <vector>  // std::vector

/**
 * @brief Shows practical usage of find results
 */
void DemonstrateFindResultUsage() {
  std::map<std::string, std::vector<int>> data_map;
  data_map["test"] = {1, 2, 3};  // Initialize with some data

  /*
   * Correct usage pattern:
   * 1. Store find result
   * 2. Check against end()
   * 3. Access if found
   */
  auto found = data_map.find("test");
  if (found != data_map.end()) {
    /*
     * The iterator points to a pair where:
     * - first is const string (key)
     * - second is vector<int> (value)
     */
    const auto& key = found->first;             // const std::string&
    std::vector<int>& numbers = found->second;  // Modifiable reference

    numbers.push_back(4);  // Can modify the vector
    // key = "new";        // Error: key is const
  }
}

/**
 * @brief Compares iterator types for const correctness
 */
void ShowConstCorrectness() {
  const std::map<std::string, std::vector<int>> const_map = {
      {"const", {1, 2, 3}}};

  /*
   * When working with const maps:
   * - Must use const_iterator
   * - Values are also const
   */
  auto const_it = const_map.find("const");
  if (const_it != const_map.end()) {
    const std::vector<int>& numbers = const_it->second;
    // numbers.push_back(4);  // Error: cannot modify const value
  }

  /*
   * Non-const map allows both:
   * - iterator (modifiable)
   * - const_iterator (read-only)
   */
  std::map<std::string, std::vector<int>> mutable_map;
  mutable_map.find("any");  // Returns mutable iterator
}

int main() {
  std::map<std::string, std::vector<int>> word_numbers;

  /*
   * Proper result variable declaration:
   *
   * 1. Use map's iterator type
   * 2. Should be const_iterator if not modifying
   * 3. Initialize with find() call
   */
  std::map<std::string, std::vector<int>>::iterator result =
      word_numbers.find("example");

  DemonstrateFindResultUsage();

  ShowConstCorrectness();

  return 0;
}
