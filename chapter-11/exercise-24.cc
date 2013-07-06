/*
 * Exercise 11.24: What does the following program do?
 *     map<int, int> m;
 *     m[0] = 1;
 */

#include <map>  // std::map

int main() {
  std::map<int, int> m;

  /*
   * Key observation points:
   *
   * 1. When the key (0) doesn't exist in the map:
   *    - The subscript operator creates a new element
   *    - The new element is value-initialized (0 for int)
   *    - Returns reference to this new element
   *
   * 2. The assignment then sets this new element's value to 1
   *
   * Equivalent explicit implementation:
   *
   * if (m.find(0) == m.end()) {
   *   m.insert({0, 0});  // Value-initialize
   * }
   * m.find(0)->second = 1;  // Then assign
   *
   * This shows the actual complexity hidden by the subscript
   */
  m[0] = 1;

  /*
   * insert vs subscript comparison:
   *
   * m.insert({0, 1});  // Only inserts if key doesn't exist
   * m[0] = 1;          // Always modifies the value
   *
   * The subscript version is more convenient when you want
   * to either insert or update existing values
   */
  m.insert({0, 1});  // Only succeeds if key 0 doesn't exist
  m[1] = 2;          // Will insert if needed, then assign

  return 0;
}
