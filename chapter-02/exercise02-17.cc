/*
 * Exercise 2.17: What does the following code print?
 *     int i, &ri = i;
 *     i = 5; ri = 10;
 *     std::cout << i << " " << ri << std::endl;
 */

#include <iostream>  // std::cout

int main() {
  int i, &ri = i;
  i = 5;
  ri = 10;
  std::cout << i << " " << ri << std::endl;

  return 0;
}

/*
 * $ g++ -o main exercise02-17.cc && ./main
 * 10 10
 */
