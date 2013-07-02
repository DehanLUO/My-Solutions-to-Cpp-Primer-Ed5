/*
 * Exercise 1.10: In addition to the ++ operator that adds 1 to its operand,
 * there is a decrement operator (--) that subtracts 1. Use the decrement
 * operator to write a while that prints the numbers from ten down to zero.
 */
#include <iostream>  // std::cout

int main() {
  int num = 10;
  while (num >= 0) {
    std::cout << num-- << " ";
  }

  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise-10.cc && ./main
 * 10 9 8 7 6 5 4 3 2 1 0
 */