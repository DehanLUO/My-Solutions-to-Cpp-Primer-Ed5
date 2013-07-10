/*
 * Exercise 14.34: Define a function-object class to perform an if-then-else
 * operation: The call operator for this class should take three parameters. It
 * should test its first parameter and if that test succeeds, it should return
 * its second parameter; otherwise, it should return its third parameter.
 */

#include <iostream>  // std::cout

class IfElseThen {
 public:
  int operator()(int a, int b, int c) { return a ? b : c; }
};

int main() {
  IfElseThen var;

  std::cout << var(1, 2, 3) << '\n';
  std::cout << var(0, 2, 3) << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-34.cc && ./main
 * 2
 * 3
 */
