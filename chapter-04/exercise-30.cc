/*
 * Exercise 4.30: Using Table 4.12 (p. 166), parenthesize the following
 * expressions to match the default evaluation:
 *     (a) sizeof x + y
 *     (b) sizeof p->mem[i]
 *     (c) sizeof a < b
 *     (d) sizeof f()
 */

#include <iostream>  // std::cout

struct Test {
  int mem[10];
};

int f() { return 42; }

int main() {
  int x = 10, y = 20;
  Test* p = new Test();
  int i = 2;
  int a = 5, b = 10;

  // (a) sizeof x + y
  std::cout << "a) Original: sizeof x + y: " << sizeof x + y << '\n';
  std::cout << "   Parenthesized: (sizeof x) + y\n";
  std::cout << "   Result: " << (sizeof x) + y << "\n\n";

  // (b) sizeof p->mem[i]
  std::cout << "b) Original: sizeof p->mem[i]: " << sizeof p->mem[i] << '\n';
  std::cout << "   Parenthesized: sizeof(p->mem[i])\n";
  std::cout << "   Result: " << sizeof(p->mem[i]) << "\n\n";

  // (c) sizeof a < b
  std::cout << "c) Original: sizeof a < b: " << (sizeof a < b) << '\n';
  std::cout << "   Parenthesized: (sizeof a) < b\n";
  std::cout << "   Result: " << ((sizeof a) < b) << "\n\n";

  // (d) sizeof f()
  std::cout << "d) Original: sizeof f(): " << sizeof f() << '\n';
  std::cout << "   Parenthesized: sizeof(f())\n";
  std::cout << "   Result: " << sizeof(f()) << "\n";

  delete p;

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-30.cc && ./main
 * a) Original: sizeof x + y: 24
 *    Parenthesized: (sizeof x) + y
 *    Result: 24
 *
 * b) Original: sizeof p->mem[i]: 4
 *    Parenthesized: sizeof(p->mem[i])
 *    Result: 4
 *
 * c) Original: sizeof a < b: 1
 *    Parenthesized: (sizeof a) < b
 *    Result: 1
 *
 * d) Original: sizeof f(): 4
 *    Parenthesized: sizeof(f())
 *    Result: 4
 */
