/*
 * Exercise 13.30: Write and test a swap function for your valuelike version of
 * HasPtr. Give your swap a print statement that notes when it is executed.
 */

#include "exercise-30.h"  // HasPtr, swap

#include <iostream>  // std::cout;

int main() {
  std::cout << "=== Creating first HasPtr ===\n";
  HasPtr hp1("Hello World");
  std::cout << "hp1 content: " << *hp1 << '\n';

  std::cout << "=== Creating second HasPtr ===\n";
  HasPtr hp2("Goodbye World");
  *hp2 = "Changed World";  // Test assignment
  std::cout << "hp2 content: " << *hp2 << "\n";

  std::cout << "=== Performing swap ===\n";
  swap(hp1, hp2);
  std::cout << "After swap:\n";
  std::cout << "hp1 content: " << *hp1 << "\n";
  std::cout << "hp2 content: " << *hp2 << "\n\n";

  std::cout << "=== Testing copy construction ===\n";
  HasPtr hp3(hp1);
  std::cout << "hp3 content: " << *hp3 << "\n\n";

  std::cout << "=== Test copy assignment ===\n";
  hp2 = hp1;  // Test copy assignment
  std::cout << "hp2 content: " << *hp2 << "\n";

  std::cout << "=== End of scope - destruction ===\n";
  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-30.cc && ./main
 * === Creating first HasPtr ===
 * hp1 content: Hello World
 * === Creating second HasPtr ===
 * hp2 content: Changed World
 * === Performing swap ===
 * ==> Executing swap between "Hello World" and "Changed World"
 * After swap:
 * hp1 content: Changed World
 * hp2 content: Hello World
 *
 * === Testing copy construction ===
 * hp3 content: Changed World
 *
 * === Test copy assignment ===
 * hp2 content: Changed World
 * === End of scope - destruction ===
 */
