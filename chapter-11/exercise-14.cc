/*
 * Exercise 11.14: Extend the map of children to their family name that you
 * wrote for the exercises in § 11.2.1 (p. 424) by having the vector store a
 * pair that holds a child’s name and birthday.
 */

#include <iostream>  // std::cout
#include <map>       // std::map
#include <string>    // std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

using ChildInfo = std::pair<std::string, std::string>;  // name, birthday
using FamilyMap = std::map<std::string, std::vector<ChildInfo>>;

/**
 * @brief Adds a new family to the map
 * @param families The family map to modify
 * @param last_name The family's last name
 */
void AddNewFamily(FamilyMap& families, const std::string& last_name) {
  families[last_name];  // Creates empty vector if doesn't exist
}

/**
 * @brief Adds a child with birthday to an existing family
 * @param families The family map to modify
 * @param last_name The family's last name
 * @param child_name The child's name
 * @param birthday The child's birthday (format: YYYY-MM-DD)
 */
void AddChild(FamilyMap& families, const std::string& last_name,
              const std::string& child_name, const std::string& birthday) {
  families[last_name].emplace_back(child_name, birthday);
}

/**
 * @brief Prints all families and their children with birthdays
 * @param families The family map to print
 */
void PrintFamilies(const FamilyMap& families) {
  for (const auto& family : families) {
    std::cout << "The " << family.first << " family has "
              << family.second.size() << " child"
              << (family.second.size() != 1 ? "ren" : "") << ":\n";
    for (const auto& detail : family.second) {
      std::cout << "  - " << detail.first << " (born " << detail.second
                << ")\n";
    }
    std::cout << '\n';
  }
}

int main() {
  FamilyMap families;

  // Add new families
  AddNewFamily(families, "Smith");
  AddNewFamily(families, "Johnson");

  // Add children with birthdays
  AddChild(families, "Smith", "Alice", "2010-05-15");
  AddChild(families, "Smith", "Bob", "2012-08-22");
  AddChild(families, "Johnson", "Charlie", "2009-03-10");
  AddChild(families, "Smith", "David", "2012-11-03");
  AddChild(families, "Johnson", "Eve", "2013-07-05");

  // Print all families
  PrintFamilies(families);

  // Add a new family with children
  families["Williams"] = {{"Frank", "2008-04-25"}, {"Grace", "2008-06-12"}};
  AddChild(families, "Williams", "Henry", "2009-02-28");

  std::cout << "After adding Williams family:\n";
  PrintFamilies(families);

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-14.cc && ./main
 * The Johnson family has 2 children:
 *   - Charlie (born 2009-03-10)
 *   - Eve (born 2013-07-05)
 *
 * The Smith family has 3 children:
 *   - Alice (born 2010-05-15)
 *   - Bob (born 2012-08-22)
 *   - David (born 2012-11-03)
 *
 * After adding Williams family:
 * The Johnson family has 2 children:
 *   - Charlie (born 2009-03-10)
 *   - Eve (born 2013-07-05)
 *
 * The Smith family has 3 children:
 *   - Alice (born 2010-05-15)
 *   - Bob (born 2012-08-22)
 *   - David (born 2012-11-03)
 *
 * The Williams family has 3 children:
 *   - Frank (born 2008-04-25)
 *   - Grace (born 2008-06-12)
 *   - Henry (born 2009-02-28)
 *
 */
