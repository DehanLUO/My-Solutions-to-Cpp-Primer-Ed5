/*
 * Exercise 11.23: Rewrite the map that stored vectors of children’s names with
 * a key that is the family last name for the exercises in § 11.2.1 (p. 424) to
 * use a multimap.
 */

/*
 * Key differences from the original map<vector<string>> approach:
 *
 * 1. Each child is stored as a separate entry in the multimap
 * 2. No need to explicitly create empty vectors for new families
 * 3. All children with the same last name are automatically grouped
 * 4. Lookup requires equal_range instead of direct key access
 */

#include <iostream>  // std::cout
#include <map>       // std::multimap
#include <string>    // std::string
#include <utility>   // std::pair

using FamilyMultimap = std::multimap<std::string, std::string>;

/**
 * @brief Prints all families and their children
 * @param families The family multimap to print
 */
void PrintFamilies(const FamilyMultimap& families) {
  /*
   * Retrieving and printing family information
   *
   * The equal_range method returns a pair of iterators marking
   * the beginning and end of the range for a given key
   */
  for (auto it = families.begin(); it != families.end();) {
    const auto& last_name = it->first;
    auto range = families.equal_range(last_name);

    /*
     * Calculate number of children by counting elements in range
     */
    size_t child_count = std::distance(range.first, range.second);

    std::cout << "The " << last_name << " family has " << child_count
              << (child_count != 1 ? " children" : " child") << ":\n";

    /*
     * Iterate through all children in this family's range
     */
    for (auto child_it = range.first; child_it != range.second; ++child_it) {
      std::cout << "  - " << child_it->second << '\n';
    }
    std::cout << '\n';

    /*
     * Advance outer iterator to end of current family's range
     * to avoid processing the same family multiple times
     */
    it = range.second;
  }
}

int main() {
  FamilyMultimap families;

  /*
   * Inserting elements - each child creates a new multimap entry
   *
   * The insert operation takes pair<const string, string> where:
   * - first is the family name (key)
   * - second is the child name (value)
   */
  families.insert({"Smith", "Bob"});
  families.insert({"Johnson", "Charlie"});
  families.insert({"Smith", "David"});
  families.insert({"Johnson", "Eve"});
  families.insert({"Williams", "Frank"});
  families.insert({"Williams", "Grace"});
  families.insert({"Williams", "Henry"});

  PrintFamilies(families);

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-23.cc && ./main
 * The Johnson family has 2 children:
 *   - Charlie
 *   - Eve
 *
 * The Smith family has 3 children:
 *   - Alice
 *   - Bob
 *   - David
 *
 * The Williams family has 3 children:
 *   - Frank
 *   - Grace
 *   - Henry
 *
 */
