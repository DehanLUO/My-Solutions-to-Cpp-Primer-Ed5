/*
 * Exercise 1.13: Rewrite the first two exercises from § 1.4.1 (p. 13) using for
 * loops.
 */

#include <iostream>  // std::cout

int main() {
  {  // Rewrite Exercise 1.9
    int sum = 0;
    for (int num = 50; num <= 100; ++num) sum += num;

    std::cout << sum << '\n';
  }

  {  // Rewrite Exercise 1.10
    for (int num = 10; num >= 0; --num) std::cout << num << " ";
    std::cout << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main exercise-13.cc && ./main
 * 3825
 * 10 9 8 7 6 5 4 3 2 1 0
 */