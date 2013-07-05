/*
 * Exercise 9.8: What type should be used to read elements in a list of strings?
 * To write them?
 */

#include <iostream>  // std::cout
#include <list>      // std::list
#include <string>    // std::string

/**
 * @brief Recommended iterator types for list<string>
 *
 * For reading (const access):
 * - std::list<std::string>::const_iterator
 *
 * For writing (non-const access):
 * - std::list<std::string>::iterator
 *
 * Rationale:
 * 1. Matches container interface requirements
 * 2. Provides proper const-correctness
 * 3. Maintains encapsulation
 */

void DemonstrateIterators() {
  std::list<std::string> words{
      "apple",
      "banana",
      "cherry",
  };

  // Writing elements (non-const access)
  for (std::list<std::string>::iterator it = words.begin(); it != words.end();
       ++it) {
    *it = "orange";  // Modifying access
  }

  // Modern alternative (auto)
  for (auto it = words.begin(); it != words.end(); ++it) {
    *it += "_modified";  // Type deduced correctly
  }

  // Reading elements (const access)
  for (std::list<std::string>::const_iterator it = words.cbegin();
       it != words.cend(); ++it) {
    std::cout << *it << '\n';  // Read-only access
  }
}

int main() {
  DemonstrateIterators();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-08.cc && ./main
 * orange_modified
 * orange_modified
 * orange_modified
 */
