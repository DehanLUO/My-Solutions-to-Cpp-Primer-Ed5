/*
 * Exercise 7.10: What does the condition in the following if statement do?
 *     if (read(read(cin, data1), data2))
 */

#include <iostream>  // std::cout

#include "exercise-09.h"

/*
 * Analysis of nested read operations in conditional statement
 * Demonstrates stream operation chaining and state checking
 */
#include <iostream>  // std::cin, std::cout
#include <string>    // std::string

int main() {
  Person data1, data2;

  /*
   * The conditional expression breakdown:
   * 1. Inner read(cin, data1) executes first:
   *    - Reads data into data1 from cin
   *    - Returns reference to cin (now potentially in fail state)
   * 2. Outer read executes with cin's current state:
   *    - Reads data into data2 if first read succeeded
   *    - Returns reference to cin
   * 3. if statement evaluates the returned stream's:
   *    - Boolean conversion (via operator bool())
   *    - True only if both reads succeeded
   */
  if (Person::Read(Person::Read(std::cin, data1), data2)) {
    std::cout << "Both reads succeeded\n";
  } else {
    std::cout << "One or both reads failed\n";
  }

  return 0;
}
