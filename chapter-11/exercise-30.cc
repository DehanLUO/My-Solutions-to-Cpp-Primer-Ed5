/*
 * Exercise 11.30: Explain the meaning of the operand pos.first->second used in
 * the output expression of the final program in this section.
 */

#include <cassert>   // static_assert
#include <iostream>  // std::cout
#include <map>       // std::multimap
#include <string>    // std::string

#include "../include/type_util.h"

/**
 * @brief Demonstrates multimap iterator dereferencing
 *
 * Examines the exact meaning and operation sequence of
 * pos.first->second when working with equal_range results
 * in std::multimap operations.
 */
void DemonstrateIteratorDereferencing() {}

/**
 * @brief Shows type-level breakdown of the expression
 *
 * Provides compile-time type analysis of each component
 * in the iterator dereferencing chain.
 */
void ShowTypeBreakdown() {
  std::multimap<std::string, int> sample;
  std::pair<std::multimap<std::string, int>::iterator,
            std::multimap<std::string, int>::iterator>
      range = sample.equal_range("test");
}

int main() {
  std::multimap<std::string, std::string> authors = {
      {"Barth, John", "Sot-Weed Factor"},
      {"Barth, John", "Lost in the Funhouse"},
      {"Smith, Alice", "Wonderland"},
      {"Smith, Alice", "Looking Glass"}};

  /*
   * equal_range returns a pair of iterators:
   * - first: lower_bound (inclusive start)
   * - second: upper_bound (exclusive end)
   */
  auto pos = authors.equal_range("Barth, John");

  /*
   * Breaking down pos.first->second:
   *
   * 1. pos: pair<iterator, iterator>
   * 2. pos.first: iterator to first matching element
   * 3. ->: dereferences iterator to access element
   * 4. second: accesses the value part of the key-value pair
   */
  while (pos.first != pos.second) {
    /*
     * Equivalent to:
     * auto& element = *(pos.first);  // dereference iterator
     * std::cout << element.second << '\n';
     */
    std::cout << pos.first->second << '\n';
    ++pos.first;
  }

  /*
   * Type analysis:
   * 1. range: pair<multimap<string,int>::iterator,
   *                 multimap<string,int>::iterator>
   * 2. range.first: multimap<string,int>::iterator
   * 3. range.first->: pair<const string, int>&
   * 4. range.first->second: int&
   */
  static_assert(
      std::is_same<decltype((pos.first->second)), std::string&>::value,
      "pos.first->second should be mutable reference (std::string&)");

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-30.cc && ./main
 * Sot-Weed Factor
 * Lost in the Funhouse
 */
