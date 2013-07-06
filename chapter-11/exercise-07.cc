/*
 * Exercise 11.7: Define a map for which the key is the family’s last name and
 * the value is a vector of the children’s names. Write code to add new families
 * and to add new children to an existing family.
 */

#include <iostream>  // std::cout
#include <map>       // std::map
#include <string>    // std::string
#include <vector>    // std::vector

using FamilyMap = std::map<std::string, std::vector<std::string>>;

/**
 * @brief Adds a new family to the map
 * @param families The family map to modify
 * @param last_name The family's last name
 */
void AddNewFamily(FamilyMap& families, const std::string& last_name) {
  families[last_name];  // Creates empty vector if doesn't exist
}

/**
 * @brief Adds a child to an existing family
 * @param families The family map to modify
 * @param last_name The family's last name
 * @param child_name The child's name to add
 */
void AddChild(FamilyMap& families, const std::string& last_name,
              const std::string& child_name) {
  families[last_name].push_back(child_name);
}

/**
 * @brief Prints all families and their children
 * @param families The family map to print
 */
void PrintFamilies(const FamilyMap& families) {
  for (const auto& family : families) {
    std::cout << "The " << family.first << " family has "
              << family.second.size() << " child"
              << (family.second.size() != 1 ? "ren" : "") << ":\n";
    for (const auto& child : family.second) {
      std::cout << "  - " << child << '\n';
    }
    std::cout << '\n';
  }
}

int main() {
  FamilyMap families;

  // Add new families
  AddNewFamily(families, "Smith");
  AddNewFamily(families, "Johnson");

  // Add children to families
  AddChild(families, "Smith", "Alice");
  AddChild(families, "Smith", "Bob");
  AddChild(families, "Johnson", "Charlie");
  AddChild(families, "Smith", "David");
  AddChild(families, "Johnson", "Eve");

  // Print all families
  PrintFamilies(families);

  // Add a new family with children
  families["Williams"] = {"Frank", "Grace"};  // Alternative initialization
  AddChild(families, "Williams", "Henry");

  std::cout << "After adding Williams family:\n";
  PrintFamilies(families);

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-07.cc && ./main
 * The Johnson family has 2 children:
 *   - Charlie
 *   - Eve
 *
 * The Smith family has 3 children:
 *   - Alice
 *   - Bob
 *   - David
 *
 * After adding Williams family:
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
