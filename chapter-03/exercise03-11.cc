//
// Exercise 3.11: Is the following range for legal? If so, what is the type of
// c?
//     const string s = "Keep out!";
//     for (auto &c : s) { /* ... */ }

#include <iostream>  // std::cout
#include <mutex>     // std::once_flag, std::call_once
#include <string>    // std::string

#include "../include/type_util.h"  // PRINT_VAR_TYPE

int main() {
  /*
   * When `s` is `const std::string`, all its members inherit `const`
   * qualification.
   */
  const std::string s = "Keep out!";

  auto it = s.begin();
  PRINT_VAR_TYPE(it);    // std::__1::__wrap_iter<char const*>
  PRINT_VAR_TYPE(*it);   // char const &
  PRINT_VAR_TYPE(s[1]);  // char const &

  std::once_flag flag;
  /*
   * Range-for uses `const`-qualified iterators for `const` containers:
   * - `s.begin()` return s `const_iterator`
   * - `*const_iteraotr` yields `char const &`
   * `auto&` in range-for must preserve `const` to maintain type safety:
   */
  for (auto &c : s) {
    std::call_once(flag, [&]() {
      PRINT_VAR_TYPE(c);  // char const &
    });

    std::cout << c;
  }
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise03-11.cc && ./main
 * it: <value not printable> | type: std::__1::__wrap_iter<char const*>
 * *it: K|type: char const &
 * s[1]: e|type: char const &
 * c: K|type: char const &
 * Keep out!
 */