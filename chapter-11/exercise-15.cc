/*
 * Exercise 11.15: What are the mapped_type, key_type, and value_type of a map
 * from int to vector<int>?
 */

#include <cassert>  // static_assert
#include <map>      // std::map
#include <vector>   // std::vector

int main() {
  using MapType = std::map<int, std::vector<int>>;

  static_assert(std::is_same<MapType::key_type, int>::value,
                "key_type should be int");
  static_assert(std::is_same<MapType::mapped_type, std::vector<int>>::value,
                "mapped_type should be vector<int>");
  static_assert(std::is_same<MapType::value_type,
                             std::pair<const int, std::vector<int>>>::value,
                "value_type should be pair<const int, vector<int>>");

  return 0;
}
