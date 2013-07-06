/*
 * Exercise 10.13: The library defines an algorithm named partition that takes a
 * predicate and partitions the container so that values for which the predicate
 * is true appear in the first part and those for which the predicate is false
 * appear in the second part. The algorithm returns an iterator just past the
 * last element for which the predicate returned true. Write a function that
 * takes a string and returns a bool indicating whether the string has five
 * characters or more. Use that function to partition words. Print the elements
 * that have five or more characters.
 */

#include <algorithm>  // std::partition
#include <iostream>   // std::cout
#include <string>     // std::string
#include <vector>     // std::vector

/**
 * @brief Predicate checking if string has 5 or more characters
 * @param s The string to check
 * @return True if length >= 5, false otherwise
 */
bool HasFiveOrMoreChars(const std::string& s) { return s.length() >= 5; }

/**
 * @brief Partitions and prints strings based on length
 * @param words The vector of strings to process
 *
 * Demonstrates:
 * 1. Using partition to rearrange elements
 * 2. Preserving original order within partitions (use stable_partition if
 * needed)
 * 3. Accessing the partitioned ranges
 */
void PartitionAndPrintByLength(std::vector<std::string>& words) {
  std::cout << "Original vector:\n";
  for (const auto& word : words) {
    std::cout << word << ' ';
  }
  std::cout << "\n\n";

  // Partition the vector
  auto partition_point =
      std::partition(words.begin(), words.end(), HasFiveOrMoreChars);

  std::cout << "After partition:\n";
  for (const auto& word : words) {
    std::cout << word << ' ';
  }
  std::cout << "\n\n";

  // Print elements with >=5 characters
  std::cout << "Strings with 5+ characters:\n";
  for (auto it = words.begin(); it != partition_point; ++it) {
    std::cout << *it << ' ';
  }
  std::cout << "\n";
}

int main() {
  std::vector<std::string> words = {"apple", "banana", "pear", "orange",
                                    "kiwi",  "grape",  "fig"};

  PartitionAndPrintByLength(words);

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-13.cc && ./main
 * Original vector:
 * apple banana pear orange kiwi grape fig
 *
 * After partition:
 * apple banana grape orange kiwi pear fig
 *
 * Strings with 5+ characters:
 * apple banana grape orange
 */
