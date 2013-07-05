/*
 * Exercise 9.9: What is the difference between the begin and cbegin functions?
 */

#include <string>  // std::string
#include <vector>  // std::vector

/**
 * @brief Key differences between begin() and cbegin()
 *
 * 1. Return Type:
 *    - begin(): returns container<T>::iterator
 *    - cbegin(): returns container<T>::const_iterator
 *
 * 2. Mutability:
 *    - begin(): allows element modification
 *    - cbegin(): read-only access
 *
 * 3. Container Overloads:
 *    - Non-const containers: both available
 *    - Const containers: begin() returns const_iterator
 *
 * 4. Intention Signaling:
 *    - cbegin() explicitly declares read-only intent
 */
void DemonstrateDifferences() {
  std::vector<std::string> colors{"red", "green", "blue"};
  const std::vector<std::string> const_colors{"cyan", "magenta", "yellow"};

  // Case 1: Non-const container
  auto it1 = colors.begin();    // vector<string>::iterator
  *it1 = "RED";                 // Allowed: can modify
  auto cit1 = colors.cbegin();  // vector<string>::const_iterator
  // *cit1 = "GREEN";           // Error: cannot modify

  // Case 2: Const container
  auto it2 = const_colors.begin();    // Returns const_iterator
  auto cit2 = const_colors.cbegin();  // Also returns const_iterator
  // *it2 = "CYAN";                   // Error for both
}

int main() {
  DemonstrateDifferences();

  return 0;
}
