/*
 * Exercise 10.42: Reimplement the program that eliminated duplicate words that
 * we wrote in § 10.2.3 (p. 383) to use a list instead of a vector.
 */

#include <iostream>  // std::cout
#include <list>      // std::list
#include <string>    // std::string

/**
 * @brief Eliminates duplicate words in a list
 * @param words The list of strings to process
 *
 * Takes advantage of list's O(1) splice operations to avoid
 * the sort+unique+erase pattern needed for vectors
 */
void ElimDups(std::list<std::string>& words) {
  // 1. Sort the list (uses list's sort member function)
  words.sort();

  // 2. Use list's unique member function to eliminate duplicates
  words.unique();

  // No erase needed - list::unique already removes duplicates
}

int main() {
  std::list<std::string> words = {"apple", "orange", "banana",
                                  "apple", "grape",  "banana"};

  std::cout << "Original list: ";
  for (const auto& word : words) {
    std::cout << word << " ";
  }
  std::cout << "\n";

  ElimDups(words);

  std::cout << "After ElimDups: ";
  for (const auto& word : words) {
    std::cout << word << " ";
  }
  std::cout << "\n";

  return 0;
}

/*
 * $ g++ -o main chapter-10/exercise-42.cc && ./main
 * Original list: apple orange banana apple grape banana
 * After ElimDups: apple banana grape orange
 */
