/*
 * Exercise 6.6: Explain the differences between a parameter, a local variable,
 * and a local static variable. Give an example of a function in which each
 * might be useful.
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Demonstrates parameter usage
 * @param name A parameter - receives value from caller
 *
 * Parameters:
 * - Defined in function declaration
 * - Initialized when function is called
 * - Act as local variables inside function
 * - Lifetime: Function execution duration
 */
void Greet(const std::string& name) {  // 'name' is a parameter
  std::cout << "Hello, " << name << "!\n";
}

/**
 * @brief Demonstrates local variable usage
 * @param x Input value to process
 * @return Processed result
 *
 * Local Variables:
 * - Defined inside function body
 * - Created when declaration is reached
 * - Destroyed when block ends
 * - Not preserved between calls
 */
int ProcessValue(int x) {
  int result = x * 2;  // 'result' is a local variable
  return result;
}

/**
 * @brief Demonstrates static local variable usage
 * @return Current call count
 *
 * Static Local Variables:
 * - Defined inside function with 'static' keyword
 * - Initialized only once (first call)
 * - Preserves value between calls
 * - Lifetime: Entire program execution
 */
int CallCounter() {
  static int count = 0;  // 'count' is a static local variable
  return ++count;
}

/*
 * Comparison Summary:
 *
 * 1. Parameters:
 *    - Pass values into functions
 *    - Example: Configuration options
 *    - Destroyed when function ends
 *
 * 2. Local Variables:
 *    - Temporary storage
 *    - Example: Intermediate calculations
 *    - Cleaned up automatically
 *
 * 3. Static Local Variables:
 *    - Maintain state between calls
 *    - Example: Call counters, caches
 *    - Persist for program lifetime
 */

int main() {
  // Parameter example
  Greet("Alice");  // "name" parameter receives "Alice"

  // Local variable example
  int val = ProcessValue(5);  // "result" created and destroyed inside

  // Static local variable example
  std::cout << "Function called " << CallCounter() << " times\n";  // 1
  std::cout << "Function called " << CallCounter() << " times\n";  // 2

  return 0;
}

/* $ g++ -o main chapter-06/exercise-06.cc && ./main
 * Hello, Alice!
 * Function called 1 times
 * Function called 2 times
 */
