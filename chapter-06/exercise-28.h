/*
 * Exercise 6.28: In the second version of error_msg that has an ErrCode
 * parameter, what is the type of elem in the for loop?
 *     void error_msg(ErrCode e, initializer_list<string> il) {
 *       cout << e.msg() << ": ";
 *       for (const auto& elem : il)
 *         cout << elem << ' ';
 *       cout << endl;
 *     }
 */

#include <initializer_list>  // std::initializer_list
#include <iostream>          // std::cout
#include <string>            // std::string

class ErrCode {
 public:
  std::string msg();
};

void error_msg(ErrCode e, std::initializer_list<std::string> il) {
  std::cout << e.msg() << ": ";
  /*
   * The type of `elem` in the ranged-based for loop is `const std::string&`
   *  - `const`: The elements cannot be modified since `initializer_list`
   *    elements are always const
   *  - `auto&`: A reference to automatically deduced type
   *  - Actual type deduced: `std::string` because `il` is an
   *    `initializer_list<string>`
   */
  for (const auto& elem : il) std::cout << elem << ' ';
  std::cout << '\n';
}
