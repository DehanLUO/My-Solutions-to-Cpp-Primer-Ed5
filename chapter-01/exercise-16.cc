/*
 * Exercise 1.16: Write your own version of a program that prints the sum of a
 * set of integers read from cin.
 */

#include <iostream>  // std::cin, std::cout

int main() {
  int sum = 0;
  int value = 0;

  std::cout << "Enter some nums. Use Ctrl+D to terminate.\n";
  while (std::cin >> value) {
    sum += value;
  }

  std::cout << "Σ(inputs) = " << sum << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise-16.cc && ./main
 * Enter some nums. Use Ctrl+D to terminate.
 * 1 2 3 4 5 6 7 8 9 10
 * Σ(inputs) = 55
 */