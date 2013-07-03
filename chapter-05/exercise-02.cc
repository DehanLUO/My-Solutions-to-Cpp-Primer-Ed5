/*
 * Exercise 5.2: What is a block? When might you might use a block?
 */

#include <iostream>  // std::cout

// Simulated resource function
int AcquireResource() {
  std::cout << "Resource acquired\n";
  return 100;
}

int main() {
  // Example 1: Basic block (compound statement)
  {
    // Variables inside this block have local scope
    int blockVar = 42;
    std::cout << "Inside block: " << blockVar << '\n';

    // Nested block demonstrating scope hierarchy
    {
      int nestedVar = blockVar * 2;  // Can access outer block variables
      std::cout << "Nested block: " << nestedVar << '\n';
    }
    // nestedVar destroyed here (out of scope)
  }
  // blockVar destroyed here (out of scope)
  // std::cout << blockVar;  // Error: blockVar not in scope

  // Example 2: Block in control flow (variable lifetime)
  bool condition = true;
  if (condition) {
    // Variables exist only during this block execution
    std::string message = "Condition is true";
    std::cout << message << '\n';
  }  // message destroyed here
  // message not accessible here

  // Example 3: Block for resource management
  {
    int resource = AcquireResource();  // Some resource acquisition
    // Use resource...
    std::cout << "Using resource: " << resource << '\n';
  }  // Resource automatically released when going out of scope

  // Example 4: Block affecting variable shadowing
  int x = 10;
  {
    int x = 20;                             // Shadows the outer x
    std::cout << "Inner x: " << x << '\n';  // 20
  }
  std::cout << "Outer x: " << x << '\n';  // 10

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-02.cc && ./main
 * Inside block: 42
 * Nested block: 84
 * Condition is true
 * Resource acquired
 * Using resource: 100
 * Inner x: 20
 * Outer x: 10
 */
