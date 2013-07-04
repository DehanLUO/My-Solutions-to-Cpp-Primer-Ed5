/*
 * Exercise 6.56: Call each element in the vector and print their result.
 */

#include <iostream>  // std::cout, std::cerr
#include <vector>    // std::vector

// Function implementations
int Add(int a, int b) { return a + b; }

int Subtract(int a, int b) { return a - b; }

int Multiply(int a, int b) { return a * b; }

int Divide(int a, int b) {
  if (b == 0) {
    std::cerr << "Error: Division by zero" << '\n';
    return 0;
  }
  return a / b;
}

// Function pointer type alias
using ArithmeticFunction = int (*)(int, int);

int main() {
  // Create and populate the function pointer vector
  std::vector<ArithmeticFunction> operations = {Add, Subtract, Multiply,
                                                Divide};

  // Test the functions through the vector
  int x = 10, y = 5;
  const char* op_names[] = {"Add", "Subtract", "Multiply", "Divide"};

  for (size_t i = 0; i < operations.size(); ++i) {
    std::cout << op_names[i] << "(" << x << ", " << y
              << ") = " << operations[i](x, y) << '\n';
  }

  return 0;
}

/* $ g++ -o main chapter-06/exercise-56.cc && ./main
 * Add(10, 5) = 15
 * Subtract(10, 5) = 5
 * Multiply(10, 5) = 50
 * Divide(10, 5) = 2
 */
