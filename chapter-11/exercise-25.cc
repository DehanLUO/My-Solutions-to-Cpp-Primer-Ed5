/*
 * Exercise 11.25: Contrast the following program with the one in the previous
 * exercise
 *     vector<int> v;
 *     v[0] = 1;
 */

#include <iostream>   // std::cout
#include <stdexcept>  // std::out_of_range
#include <vector>     // std::vector

int main() {
  std::vector<int> v;

  /*
   * This is UNDEFINED BEHAVIOR:
   * - v is empty (size = 0, capacity = 0)
   * - No memory allocated for elements
   * - Writing to v[0] corrupts memory
   */
  // v[0] = 1;  // NEVER DO THIS - COMMENTED OUT FOR SAFETY

  /*
   * 1. push_back (appends at end)
   * 2. insert (at specific position)
   */
  v.push_back(1);          // Properly grows vector
  v.insert(v.begin(), 2);  // Insert at beginning

  /*
   * Option 2: resize first
   */
  v.resize(3);  // v[0]-v[2] exist
  v[2] = 5;     // Safe assignment

  /*
   * Option 3: at() with bounds checking
   * (throws std::out_of_range if invalid)
   */
  try {
    v.at(1) = 3;  // Throws if index invalid
  } catch (const std::out_of_range& e) {
    std::cout << "Access error: " << e.what() << '\n';
  }

  return 0;
}
