/*
 * Exercise 11.6: Explain the difference between a set and a list. When might
 * you use one or the other?
 */

#include <ios>       // std::boolalpha
#include <iostream>  // std::cout
#include <list>      // std::list
#include <set>       // std::set
#include <string>    // std::string

int main() {
  /*
   * Key Differences Between set and list:
   *
   * 1. Data Organization:
   *    - set: Ordered unique elements (BST implementation)
   *    - list: Doubly-linked sequence of elements
   *
   * 2. Element Handling:
   *    - set: Automatically enforces uniqueness and sorting
   *    - list: Allows duplicates and maintains insertion order
   *
   * 3. Performance Characteristics:
   *    +------------------+------------+------------+
   *    | Operation        | set        | list       |
   *    +------------------+------------+------------+
   *    | Insertion        | O(log n)   | O(1)       |
   *    | Search           | O(log n)   | O(n)       |
   *    | Delete           | O(log n)   | O(1)       |
   *    | Ordered Traversal| Yes        | No         |
   *    +------------------+------------+------------+
   *
   * 4. When to Use Each:
   *    Use set when:
   *    - You need automatic sorting and uniqueness
   *    - You frequently search for elements
   *    Example:
   */
  std::set<std::string> dictionary = {"apple", "banana", "cherry"};
  std::cout << "   Dictionary contains 'banana': " << std::boolalpha
            << static_cast<bool>(dictionary.count("banana")) << '\n';

  /*
   *    Use list when:
   *    - You need frequent insertions/deletions in middle
   *    - You need to maintain insertion order
   *    Example:
   */
  std::list<std::string> todo_list = {"Wake up", "Brush teeth", "Work"};
  todo_list.insert(std::next(todo_list.begin()), "Shower");
  std::cout << "   TODO List:";
  for (const auto& task : todo_list) std::cout << " " << task;
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-06.cc && ./main
 *    Dictionary contains 'banana': true
 *    TODO List: Wake up Shower Brush teeth Work
 */
