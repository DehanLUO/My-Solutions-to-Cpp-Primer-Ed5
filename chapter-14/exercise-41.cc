/*
 * Exercise 14.41: Why do you suppose the new standard added lambdas? Explain
 * when you would use a lambda and when you would write a class instead.
 */

#include <algorithm>  // std::for_each, std::sort
#include <iostream>   // std::cout
#include <vector>     // std::vector

/**
 * @class ComplexOperation
 * @brief Example of a complex function object that maintains state
 *
 * This class demonstrates a case where a function object is preferable to a
 * lambda due to complex state management and reusability requirements.
 */
class ComplexOperation {
 public:
  /**
   * @brief Constructs a ComplexOperation with initial configuration
   * @param base_value Base value for computations
   * @param multiplier Multiplication factor
   */
  explicit ComplexOperation(int base_value = 0L, double multiplier = 1.0F)
      : base_value_(base_value), multiplier_(multiplier), call_count_(0L) {}

  /**
   * @brief Performs complex computation with state tracking
   * @param value Input value for computation
   * @return double Result of complex operation
   * @time Complexity O(1) - constant time operation
   * @space Complexity O(1) - no additional space required
   */
  double operator()(int value) {
    ++call_count_;
    return (value + base_value_) * multiplier_;
  }

  /**
   * @brief Gets the number of times the operation has been called
   * @return int Call count
   */
  int GetCallCount() const { return call_count_; }

  /**
   * @brief Resets the call counter
   */
  void ResetCounter() { call_count_ = 0; }

 private:
  int base_value_;     // configuration parameter
  double multiplier_;  // configuration parameter
  int call_count_;     // state tracking
};

int main() {
  std::vector<int> numbers = {9, 7, 5, 3, 1, 8, 6, 4, 2, 0};

  /*
   * CASE 1: Use Lambda - Simple, one-off operations
   *
   * Lambdas are ideal for simple, localized operations that do not require
   * complex state management or reuse across multiple scopes. The syntax is
   * concise and keeps the logic close to its usage.
   */
  std::cout << "Using lambda for simple filtering:\n";
  std::for_each(numbers.begin(), numbers.end(), [](int n) {
    if (n > 5) {
      std::cout << n << ' ';
    }
  });
  std::cout << "\n\n";

  /*
   * CASE 2: Use Lambda - Capturing local context
   *
   * Lambdas excel at capturing local variables from their enclosing
   * scope, making them perfect for context-dependent operations
   * without explicit parameter passing.
   */
  int threshold = 4;
  std::cout << "Using lambda with captured variable (threshold = " << threshold
            << "):\n";
  auto count = std::count_if(numbers.begin(), numbers.end(),
                             [threshold](int n) { return n > threshold; });
  std::cout << "Numbers above threshold: " << count << "\n\n";

  /*
   * CASE 3: Use Function Object - Complex state management
   *
   * When an operation requires maintaining complex state across
   * multiple calls or needs configuration parameters, a class
   * provides better organization and encapsulation.
   */
  std::cout << "Using function object for stateful operation:\n";
  ComplexOperation complex_op(10, 2.5);
  for (int num : numbers) {
    std::cout << complex_op(num) << " ";
  }
  std::cout << "\nCall count: " << complex_op.GetCallCount() << "\n\n";

  /*
   * CASE 4: Use Function Object - Reusable library components
   *
   * For operations that need to be reused across multiple compilation
   * units or as part of a library interface, function objects provide
   * better modularity and explicit interface definition.
   */
  std::cout << "Using reusable function object:\n";
  ComplexOperation reusable_op;
  std::vector<double> results;
  for (int num : numbers) {
    results.push_back(reusable_op(num));
  }
  std::cout << "Reusable operation call count: " << reusable_op.GetCallCount()
            << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-41.cc && ./main
 * Using lambda for simple filtering:
 * 9 7 8 6
 *
 * Using lambda with captured variable (threshold = 4):
 * Numbers above threshold: 5
 *
 * Using function object for stateful operation:
 * 47.5 42.5 37.5 32.5 27.5 45 40 35 30 25
 * Call count: 10
 *
 * Using reusable function object:
 * Reusable operation call count: 10
 */
