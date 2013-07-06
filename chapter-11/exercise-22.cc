/*
 * Exercise 11.22: Given a map<string, vector<int>>, write the types used as an
 * argument and as the return value for the version of insert that inserts one
 * element.
 */

#include <map>      // std::map
#include <string>   // std::string
#include <utility>  // std::pair
#include <vector>   // std::vector

int main() {
  std::map<std::string, std::vector<int>> string_to_ints_map;

  /*
   * Return type breakdown:
   * The complete return type is:
   * pair<map<string, vector<int>>::iterator, bool>
   *
   * The iterator itself points to a value_type element
   */
  std::pair<std::map<std::string, std::vector<int>>::iterator, bool> result =
      string_to_ints_map.insert({"example", {1, 2, 3}});

  return 0;
}
