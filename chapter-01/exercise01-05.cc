/*
 * Exercise 1.5: We wrote the output in one large statement. Rewrite the program
 * to use a separate statement to print each operand.
 */
#include <iostream>  // std::cout

int main() {
  std::cout << "Enter two numbers: \n";

  int multiplier_first = 0;
  int multiplier_second = 0;
  std::cin >> multiplier_first >> multiplier_second;

  std::cout << "The product of ";
  std::cout << multiplier_first;
  std::cout << " and ";
  std::cout << multiplier_second;
  std::cout << " is ";
  std::cout << multiplier_first * multiplier_second;
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise01-05.cc && ./main
 * Enter two numbers:
 * 3 7
 * The product of 3 and 7 is 21
 */