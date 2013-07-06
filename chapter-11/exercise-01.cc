/*
 * Exercise 11.1: Describe the differences between a map and a vector.
 */

#include <iostream>  // std::cout
#include <map>       // std::map
#include <vector>    // std::vector

/*
 * Key Differences Between map and vector:
 * 1. Basic Structure:
 *    - vector: Dynamic array of elements
 *    - map: Collection of key-value pairs (balanced BST)
 * 2. Element Access:
 *    - vector: By position (v[0], v.at(1))
 *    - map: By key (m["key"], m.at("key"))
 * 3. Memory Organization:
 *    - vector: Contiguous memory blocks
 *    - map: Non-contiguous node-based storage
 * 4. Time Complexity:
 *    +----------------+------------+------------+
 *    | Operation      | vector     | map        |
 *    +----------------+------------+------------+
 *    | Access         | O(1)       | O(log n)   |
 *    | Search         | O(n)       | O(log n)   |
 *    | Insert/Delete  | O(n)       | O(log n)   |
 *    +----------------+------------+------------+
 * 5. When to Use Each:
 *    - vector: When you need:
 *      * Sequential access
 *      * Random access by position
 *      * Cache locality
 *    - map: When you need:
 *      * Fast lookup by key
 *      * Ordered traversal
 *      * Key-value associations
 */

int main() {
  // Practical demonstration
  std::vector<std::string> vec = {"apple", "banana", "cherry"};
  std::map<std::string, int> fruit_counts = {{"apple", 5}, {"banana", 3}};

  // Vector access
  std::cout << "Vector example:\n";
  std::cout << "First fruit: " << vec[0] << "\n";

  // Map access
  std::cout << "\nMap example:\n";
  std::cout << "Apple count: " << fruit_counts["apple"] << "\n";
  fruit_counts["cherry"] = 7;  // Insert new key-value pair

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-01.cc && ./main
 * Vector example:
 * First fruit: apple
 *
 * Map example:
 * Apple count: 5
 */
