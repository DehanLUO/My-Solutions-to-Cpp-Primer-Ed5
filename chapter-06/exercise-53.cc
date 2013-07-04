/*
 * Exercise 6.53: Explain the effect of the second declaration in each one of
 * the following sets of declarations. Indicate which, if any, are illegal.
 *     (a) int calc(int&, int&);
 *         int calc(const int&, const int&);
 *     (b) int calc(char*, char*);
 *         int calc(const char*, const char*);
 *     (c) int calc(char*, char*);
 *         int calc(char* const, char* const);
 */

#include <iostream>  // std::cout

/* Case (a): Reference variations */
int Calc(int&, int&);              // Original
int Calc(const int&, const int&);  // Legal overload
/*
 * Effect:
 * - Creates overload for const references
 * - Legal because parameter types are sufficiently different
 * - Allows calls with both const and non-const arguments
 */

/* Case (b): Pointer to char variations */
int Calc(char*, char*);              // Original
int Calc(const char*, const char*);  // Legal overload
/*
 * Effect:
 * - Creates overload for pointers to const char
 * - Legal because pointee constness differs
 * - Enables string literal handling (which are const char*)
 */

/* Case (c): Pointer constness variations */
int Calc(char*, char*);  // Original
// int Calc(char* const, char* const);  // Illegal redeclaration
/*
 * Problem:
 * - Top-level const on parameters is ignored in declarations
 * - Both declarations are equivalent
 * - Would cause "redefinition" error
 */

// Supporting implementations
int Calc(int& a, int& b) {
  std::cout << "Called Calc(int&, int&)\n";
  return a + b;
}

int Calc(const int& a, const int& b) {
  std::cout << "Called Calc(const int&, const int&)\n";
  return a + b;
}

int Calc(char* a, char* b) {
  std::cout << "Called Calc(char*, char*)\n";
  return *a + *b;
}

int Calc(const char* a, const char* b) {
  std::cout << "Called Calc(const char*, const char*)\n";
  return *a + *b;
}

int main() {
  // Demonstration of legal cases
  int x = 1, y = 2;
  Calc(x, y);  // Calls non-const version

  const int cx = 3, cy = 4;
  Calc(cx, cy);  // Calls const version

  char c1 = 'a', c2 = 'b';
  Calc(&c1, &c2);  // Calls char* version

  const char* s1 = "hello";
  const char* s2 = "world";
  Calc(s1, s2);  // Calls const char* version

  return 0;
}

/* $ g++ -o main chapter-06/exercise-53.cc && ./main
 * Called Calc(int&, int&)
 * Called Calc(const int&, const int&)
 * Called Calc(char*, char*)
 * Called Calc(const char*, const char*)
 */
