/*
 * Exercise 11.5: Explain the difference between a map and a set. When might you
 * use one or the other?
 */

#include <iostream>  // std::cout
#include <map>       // std::map
#include <set>       // std::set
#include <string>    // std::string

int main() {
  /*
   * Key Differences Between map and set:
   *
   * 1. Data Organization:
   *    - map: Stores key-value pairs (std::pair<const Key, Value>)
   *    - set: Stores unique keys only
   *
   * 2. Element Access:
   *    - map: Access values via keys (operator[] or at())
   *    - set: Only checks for existence (count() or find())
   *
   * 3. Memory Characteristics:
   *    - map: Stores both keys and values (more memory)
   *    - set: Stores only keys (less memory)
   *
   * 4. When to Use Each:
   *    Use map when:
   *    - You need to associate data (e.g., student ID -> name)
   *    - You need to frequently look up values by key
   *    Example:
   */

  std::map<int, std::string> student_map = {
      {101, "Alice"}, {102, "Bob"}, {103, "Charlie"}};
  std::cout << "   student_map[102] = " << student_map[102] << '\n';

  /*
   *    Use set when:
   *    - You only need to track existence/unique items
   *    - You need ordered unique elements
   */
  std::set<std::string> username_set = {"alice", "bob", "charlie"};
  std::cout << "   username_set contains 'bob': "
            << (username_set.count("bob") ? "true" : "false") << '\n';

  /*
   * 5. Performance (Both O(log n) for operations):
   *    - map: Operations work on keys only
   *    - set: Essentially a map without values
   */

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-05.cc && ./main
 *    student_map[102] = Bob
 *    username_set contains 'bob': true
 */
