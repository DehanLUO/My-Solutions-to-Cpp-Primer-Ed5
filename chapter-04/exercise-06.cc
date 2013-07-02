/*
 * Exercise 4.6: Write an expression to determine whether an int value is even
 * or odd.
 */

#include <iostream>  // std::cin, std::cout

int main() {
  int input;
  std::cout << "Enger an integer: ";
  std::cin >> input;

  // Check if even or odd using modulus operator
  if (0 == input % 2) {
    std::cout << input << " is even.\n";
  } else {
    std::cout << input << " is odd.\n";
  }

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-06.cc && ./main
 * Enger an integer: 101
 * 101 is odd.
 */