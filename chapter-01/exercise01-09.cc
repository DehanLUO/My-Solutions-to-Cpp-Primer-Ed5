/*
 * Exercise 1.9: Write a program that uses a while to sum the numbers from 50 to
 * 100.
 */
#include <iostream>  // std::cout

int main() {
  int num = 50;
  int sum = 0;
  while (num <= 100) {
    sum += num++;
  }

  std::cout << "The sum from 50 to 100 is " << sum << '\n';

  return 0;
}

/*
 * $ g++ -o main exercise01-09.cc && ./main
 * The sum from 50 to 100 is 3825
 */