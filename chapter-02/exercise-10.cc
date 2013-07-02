/*
 * Exercise 2.10: What are the initial values, if any, of each of the followin
 * variables?
 *     std::string global_str;
 *     int global_int;
 *     int main() {
 *       int local_int;
 *       std::string local_str;
 *     }
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/*
 * `global_str` is default-initialized using the default constructor of
 * std::string, which results in an empty string ("").
 */
std::string global_str;
/*
 * `global_int` is a global built-in type, so it is zero-initialized to 0 before
 * main starts, by the runtime system (in the static storage are).
 */
int global_int;

int main() {
  /*
   * `local_int` is a stack variable of built-in type. Since it has no
   * initializer, it is not initialized by default. Its memory contains
   * indeterminate value. This is a deliberate choice in c++ to avoid
   * unnecessary overhead and allow faster code execution. Using it without
   * initialization causes undefined behavior.
   */
  int local_int;

  /*
   * `local_str` is default-initialized by the constructor of std::string,
   * resulting in an empty string.
   */
  std::string local_str;

  std::cout << "global_str: " << global_str << '\n'  //
            << "global_int: " << global_int << '\n'  //
            << "local_int: " << local_int << '\n'    // garbage value
            << "local_str: " << local_str << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise-10.cc && ./main
 * global_str:
 * global_int: 0
 * local_int: 32760
 * local_str:
 */