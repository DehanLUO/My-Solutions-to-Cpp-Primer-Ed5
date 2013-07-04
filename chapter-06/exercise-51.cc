/*
 * Exercise 6.51: Write all four versions of f. Each function should print a
 * distinguishing message. Check your answers for the previous exercise. If your
 * answers were incorrect, study this section until you understand why your
 * answers were wrong.
 */

#include <iostream>  // std::cout

// Version 1: No parameters
void f() { std::cout << "Called f() - no parameters" << '\n'; }

// Version 2: Single int parameter
void f(int a) {
  std::cout << "Called f(int) - with int parameter: " << a << '\n';
}

// Version 3: Two int parameters
void f(int a, int b) {
  std::cout << "Called f(int, int) - with int parameters: " << a << ", " << b
            << '\n';
}

// Version 4: Two double parameters (second has default)
void f(double a, double b = 3.14) {
  std::cout << "Called f(double, double) - with double parameters: " << a
            << ", " << b << '\n';
}

int main() {
  // Test case (a): f(2.56, 42)
  std::cout << "Calling f(2.56, 42):" << '\n';
  // f(2.56, 42);  // Commented out because it's ambiguous
  std::cout
      << "  This call is ambiguous because:\n"
      << "  - f(int, int) requires narrowing (double->int) for first arg\n"
      << "  - f(double, double) requires promotion (int->double) for second\n"
      << "  Neither function is clearly better" << '\n';

  // Test case (b): f(42)
  std::cout << "\nCalling f(42):" << '\n';
  f(42);
  std::cout << "  Selected f(int) because:\n"
            << "  - Exact match beats f(double)'s promotion" << '\n';

  // Test case (c): f(42, 0)
  std::cout << "\nCalling f(42, 0):" << '\n';
  f(42, 0);
  std::cout << "  Selected f(int, int) because:\n"
            << "  - Exact match beats f(double,double)'s promotions" << '\n';

  // Test case (d): f(2.56, 3.14)
  std::cout << "\nCalling f(2.56, 3.14):" << '\n';
  f(2.56, 3.14);
  std::cout << "  Selected f(double, double) because:\n"
            << "  - Exact match beats f(int,int)'s narrowing conversions"
            << '\n';

  return 0;
}

/* $ g++ -o main chapter-06/exercise-51.cc && ./main
 * Calling f(2.56, 42):
 *   This call is ambiguous because:
 *   - f(int, int) requires narrowing (double->int) for first arg
 *   - f(double, double) requires promotion (int->double) for second
 *   Neither function is clearly better
 *
 * Calling f(42):
 * Called f(int) - with int parameter: 42
 *   Selected f(int) because:
 *   - Exact match beats f(double)'s promotion
 *
 * Calling f(42, 0):
 * Called f(int, int) - with int parameters: 42, 0
 *   Selected f(int, int) because:
 *   - Exact match beats f(double,double)'s promotions
 *
 * Calling f(2.56, 3.14):
 * Called f(double, double) - with double parameters: 2.56, 3.14
 *   Selected f(double, double) because:
 *   - Exact match beats f(int,int)'s narrowing conversions
 */