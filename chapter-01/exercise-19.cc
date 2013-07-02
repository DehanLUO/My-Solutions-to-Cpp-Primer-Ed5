/*
 * Exercise 1.19: Revise the program you wrote for the exercises in § 1.4.1 (p.
 * 13) that printed a range of numbers so that it handles input in which the
 * first number is smaller than the second
 */
#include <iostream>  // std::cout

int main() {
  std::cout << "Enter two numbers: \n";
  int num_a = 0;
  int num_b = 0;
  std::cin >> num_a >> num_b;

  if (num_a > num_b) {
    int temp = num_a;
    num_b = num_a;
    num_a = num_b;
  }

  while (num_a <= num_b) {
    std::cout << num_a++ << " ";
  }

  return 0;
}

/*
 * $ g++ -o main exercise-19.cc && ./main
 * Enter two numbers:
 * 10 20
 * 10 11 12 13 14 15 16 17 18 19 20
 */