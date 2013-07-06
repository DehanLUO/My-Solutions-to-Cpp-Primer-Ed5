/*
 * Exercise 11.26: What type can be used to subscript a map? What type does the
 * subscript operator return? Give a concrete example—that is, define a map and
 * then write the types that can be used to subscript the map and the type that
 * would be returned from the subscript operator.
 */

#include <cassert>      // static_assert
#include <map>          // std::map
#include <string>       // std::string
#include <type_traits>  // std::is_same

/**
 * @brief Demonstrates practical usage with custom key types
 *
 * Shows how the subscript operator behaves with
 * user-defined types as map keys.
 */
void DemonstrateCustomKeyTypes() {
  /*
   * Custom key type must meet:
   * 1. Strict weak ordering (provide < operator)
   * 2. Copyable/movable
   * 3. Comparable for equality
   */
  struct City {
    std::string name;
    std::string country;

    bool operator<(const City& other) const {
      return std::tie(name, country) < std::tie(other.name, other.country);
    }
  };

  std::map<City, int> population_map;

  /*
   * Subscript argument must be convertible to City
   * Return type is int& (mapped_type reference)
   */
  population_map[{"Toronto", "Canada"}] = 2731571;
}

int main() {
  std::map<std::string, int> word_counts;

  /*
   * Subscript requirements:
   *
   * 1. Argument type:
   *    - Must be convertible to the map's key_type
   *    - In this case: const std::string& or types convertible to string
   *
   * 2. Return type:
   *    - Returns reference to mapped_type (int& in this case)
   *    - This allows both reading and modification
   */
  word_counts["apple"] = 5;  // string literal converted to string

  /*
   * Type verification example:
   */
  static_assert(
      std::is_same<std::map<std::string, int>::key_type, std::string>::value,
      "key_type should be std::string");
  static_assert(
      std::is_same<std::map<std::string, int>::mapped_type, int>::value,
      "mapped_type should be int");
  decltype(word_counts)::key_type key = "banana";  // key_type is std::string
  decltype(word_counts)::mapped_type value;        // mapped_type is int

  /*
   * The subscript operation returns mapped_type& (int& here)
   * which allows direct modification:
   */
  word_counts[key] = value + 3;  // Returns reference to int

  DemonstrateCustomKeyTypes();

  return 0;
}
