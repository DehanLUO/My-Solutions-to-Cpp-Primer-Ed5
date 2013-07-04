/*
 * Exercise 6.49: What is a candidate function? What is a viable function?
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/*
 * Candidate functions:
 * - All functions with the matching name visible at the call point
 * - Found through name lookup (including ADL)
 */

/* Viable functions:
 * - Subset of candidate functions that could be called with given arguments
 * - Must have correct number of parameters
 * - Must have compatible parameter types (through implicit conversion)
 */

// Example 1: Supporting function declarations
void Print(int val) { std::cout << "Integer: " << val << '\n'; }
void Print(double val) { std::cout << "Double: " << val << '\n'; }
void Print(const std::string& val) { std::cout << "String: " << val << '\n'; }

template <typename T>
void Log(T val) {
  std::cout << "Template: " << val << '\n';
}

void Log(int val) { std::cout << "Non-template: " << val << '\n'; }

int main() {
  // Demonstrate candidate vs viable selection
  Print(42);       // Selects Print(int)
  Print(3.14);     // Selects Print(double)
  Print("hello");  // Selects Print(string)

  Log(10);    // Selects Log(int) over template
  Log(10.0);  // Selects template Log<double>

  return 0;
}

/* $ g++ -o main chapter-06/exercise-49.cc && ./main
 * Integer: 42
 * Double: 3.14
 * String: hello
 * Non-template: 10
 * Template: 10
 */
