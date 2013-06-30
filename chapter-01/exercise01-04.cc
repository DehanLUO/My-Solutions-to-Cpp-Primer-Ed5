/*
 * Exercise 1.4: Our program used the addition operator, +, to add two numbers.
 * Write a program that uses the multiplication operator,*, to print the product
 * instead.
 */
#include <iostream>  //std::cin, std::cout

int main() {
  std::cout << "Enter two numbers: \n";
  int multiplier_first = 0;
  int multiplier_second = 0;
  std::cin >> multiplier_first >> multiplier_second;
  std::cout << "The product of " << multiplier_first << " and "
            << multiplier_second << " is "
            << multiplier_first * multiplier_second << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise01-04.cc && ./main
 * Enter two numbers:
 * 3 7
 * The product of 3 and 7 is 21
 */