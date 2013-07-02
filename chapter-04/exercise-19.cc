/*
 * Exercise 4.19: Given that ptr points to an int, that vec is a vector<int>,
 * and that ival is an int, explain the behavior of each of these expressions.
 * Which, if any, are likely to be incorrect? Why? How might each be corrected?
 *     (a) ptr != 0 && *ptr++
 *     (b) ival++ && ival
 *     (c) vec[ival++] <= vec[ival]
 */

#include <iostream>  // std::cout

/**
 * @brief Demonstrates and corrects problematic expressions
 */
void ExplainExpressions() {
  // Setup test environment
  int x = 42;
  int* ptr = &x;
  std::vector<int> vec = {10, 20, 30, 40};
  int ival = 1;

  // Case (a): ptr != 0 && *ptr++
  {
    std::cout << "Case (a) Original: ptr != 0 && *ptr++\n";
    if (ptr != 0 && *ptr++) {  // Safe but confusing
      std::cout << "  Works but has side effect - ptr now at: " << *ptr << "\n";
    }

    // Corrected version (a):
    ptr = &x;        // Reset pointer
    if (ptr != 0) {  // Clearer separation
      std::cout << "  Corrected: " << *ptr << "\n";
      ptr++;  // Explicit increment if needed
    }
  }

  // Case (b): ival++ && ival
  {
    std::cout << "\nCase (b) Original: ival++ && ival\n";
    ival = 1;              // Reset
    if (ival++ && ival) {  // Depends on evaluation order
      std::cout << "  Dangerous - depends on evaluation order\n";
      std::cout << "  Final ival: " << ival << "\n";
      /*
       * In C++11, while the && operator guarantees left-to-right evaluation
       * (left operand first, then right operand only if needed), the issue lies
       * in when the side effect of the post-increment is applied.
       * For ival++ && ival:
       * 1. Left operand (ival++) is evaluated first, but being a
       * post-increment, it:
       *   - Returns the original value (1) for the logical operation
       *   - Schedules the increment (ival += 1) to occur before the next
       *     sequence point (but timing is unspecified)
       * 2. Right operand (ival) may read either:
       *   - The original value (1) if the increment hasn’t been applied yet
       *   - The updated value (2) if the increment was processed immediately
       * This creates undefined behavior because:
       * - The read (right operand) and write (post-increment) are
       *   unsequenced—the standard doesn’t enforce which happens first.
       * - Results depend on compiler implementation, making the code
       *   unpredictable and non-portable.
       */
    }

    // Corrected version (b):
    ival = 1;
    int old_val = ival;
    ival++;
    if (old_val && ival) {  // Explicit sequencing
      std::cout << "  Corrected: safe and clear\n";
    }
  }

  // Case (c): vec[ival++] <= vec[ival]
  {
    std::cout << "\nCase (c) Original: vec[ival++] <= vec[ival]\n";
    ival = 1;
    bool result = vec[ival++] <= vec[ival];  // Undefined behavior
    std::cout << "  UB - accesses vec[" << ival - 1 << "] and vec[" << ival
              << "] simultaneously\n";

    // Corrected version (c):
    ival = 1;
    int left = vec[ival];
    ival++;
    bool safe_result = left <= vec[ival];
    std::cout << "  Corrected: compares vec[1] and vec[2] safely\n";
  }
}

int main() {
  ExplainExpressions();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-19.cc && ./main
 * chapter-04/exercise-19.cc:78:27: warning: unsequenced modification and access to 'ival' [-Wunsequenced]
 *    78 |     bool result = vec[ival++] <= vec[ival];  // Undefined behavior
 *       |                           ^          ~~~~
 * 1 warning generated.
 * Case (a) Original: ptr != 0 && *ptr++
 *   Works but has side effect - ptr now at: 10
 *   Corrected: 42
 *
 * Case (b) Original: ival++ && ival
 *   Dangerous - depends on evaluation order
 *   Final ival: 2
 *   Corrected: safe and clear
 *
 * Case (c) Original: vec[ival++] <= vec[ival]
 *   UB - accesses vec[1] and vec[2] simultaneously
 *   Corrected: compares vec[1] and vec[2] safely
 */