/*
 * Exercise 6.54: Write a declaration for a function that takes two int
 * parameters and returns an int, and declare a vector whose elements have this
 * function pointer type.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Function that takes two ints and returns an int
 * @param a First integer parameter
 * @param b Second integer parameter
 * @return Result of operation
 */
int SampleFunction(int a, int b) {
  std::cout << "SampleFunction " << a << " + " << b << ": " << a + b << '\n';
  return a + b;  // Example implementation
}

int main() {
  // Declaration of the function pointer type
  using FunctionPtr = int (*)(int, int);

  // Vector declaration holding such function pointers
  std::vector<FunctionPtr> function_table;

  // Example usage:
  function_table.push_back(SampleFunction);  // Add function to vector
  function_table.push_back(&SampleFunction);
  function_table.push_back([](int x, int y) {
    std::cout << "[] " << x << " + " << y << ": " << x + y << '\n';
    return x * y;
  });  // Lambda

  // Calling a function from the vector
  std::cout << function_table[0](2, 3) << '\n';  // Calls SampleFunction(2, 3)
  std::cout << function_table[1](5, 8) << '\n';  // Calls [](5, 8)

  return 0;
}

/* $ g++ -o main chapter-06/exercise-51.cc && ./main
 * SampleFunction 2 + 3: 5
 * 5
 * SampleFunction 5 + 8: 13
 * 13
 */
