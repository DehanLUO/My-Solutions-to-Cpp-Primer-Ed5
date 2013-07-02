/*
 * Exercise 3.9: What does the following program do? Is it valid? If not, why
 * not?
 *     string s; cout << s[0] << endl;
 */

#include <iostream>  // std::cout
#include <string>    // std::string

int main() {
  /*
   * Invalid. `s` is default-initialized as empty. Accessing any index (even 0)
   * on an empty string is undefined per c++ standard.
   */
  std::string s;
  std::cout << s[0] << std::endl;

  return 0;
}
