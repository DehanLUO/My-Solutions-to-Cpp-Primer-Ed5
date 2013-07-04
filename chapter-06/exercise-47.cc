/*
 * Exercise 6.47: Revise the program you wrote in the exercises in § 6.3.2
 * (p.228) that used recursion to print the contents of a vector to
 * conditionally print information about its execution. For example, you might
 * print the size of the vector on each call. Compile and run the program with
 * debugging turned on and again with it turned off.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

/**
 * @brief Recursively prints vector contents with conditional debug information
 * @param vec The vector to print
 * @param index Current index (default 0)
 *
 * Uses NDEBUG macro to control debug output, showing:
 * - File name and line number
 * - Timestamp of compilation
 * - Current recursion state
 */
void PrintVectorRecursive(const std::vector<int>& vec, size_t index = 0) {
#ifndef NDEBUG
  // Debug information when NDEBUG is not defined
  std::cout << "[" << __FILE__ << ":" << __LINE__ << "] "
            << "Compiled on " << __DATE__ << " at " << __TIME__ << "\n"
            << "Debug: vec.size() = " << vec.size()
            << ", current index = " << index << "\n";
#endif

  // Base case
  if (index >= vec.size()) {
    std::cout << '\n';
    return;
  }

  // Print current element
  std::cout << vec[index] << ' ';

  // Recursive call
  PrintVectorRecursive(vec, index + 1);
}

/**
 * @brief Iterator version with debug macros
 * @param current Iterator to current element
 * @param end End iterator
 */
void PrintVectorRecursiveIt(std::vector<int>::const_iterator current,
                            std::vector<int>::const_iterator end) {
#ifndef NDEBUG
  std::cout << "[" << __FILE__ << ":" << __LINE__ << "] "
            << "Debug: remaining elements = " << (end - current) << "\n";
#endif

  if (current == end) {
    std::cout << '\n';
    return;
  }

  std::cout << *current << ' ';
  PrintVectorRecursiveIt(++current, end);
}

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5};

  // Run with debug info (NDEBUG not defined)
  std::cout << "First run (with debug info):\n";
  PrintVectorRecursive(numbers);

  // Iterator version demonstration
  std::cout << "\nIterator version:\n";
  PrintVectorRecursiveIt(numbers.begin(), numbers.end());

  return 0;
}

/* $ g++ -o main chapter-06/exercise-47.cc && ./main
 * First run (with debug info):
 * [chapter-06/exercise-47.cc:25] Compiled on Jul 04 2013 at 06:41:55
 * Debug: vec.size() = 5, current index = 0
 * 1 [chapter-06/exercise-47.cc:25] Compiled on Jul 04 2013 at 06:41:55
 * Debug: vec.size() = 5, current index = 1
 * 2 [chapter-06/exercise-47.cc:25] Compiled on Jul 04 2013 at 06:41:55
 * Debug: vec.size() = 5, current index = 2
 * 3 [chapter-06/exercise-47.cc:25] Compiled on Jul 04 2013 at 06:41:55
 * Debug: vec.size() = 5, current index = 3
 * 4 [chapter-06/exercise-47.cc:25] Compiled on Jul 04 2013 at 06:41:55
 * Debug: vec.size() = 5, current index = 4
 * 5 [chapter-06/exercise-47.cc:25] Compiled on Jul 04 2013 at 06:41:55
 * Debug: vec.size() = 5, current index = 5
 *
 *
 * Iterator version:
 * [chapter-06/exercise-47.cc:52] Debug: remaining elements = 5
 * 1 [chapter-06/exercise-47.cc:52] Debug: remaining elements = 4
 * 2 [chapter-06/exercise-47.cc:52] Debug: remaining elements = 3
 * 3 [chapter-06/exercise-47.cc:52] Debug: remaining elements = 2
 * 4 [chapter-06/exercise-47.cc:52] Debug: remaining elements = 1
 * 5 [chapter-06/exercise-47.cc:52] Debug: remaining elements = 0
 *
 * $ g++ -D NDEBUG -o main chapter-06/exercise-47.cc && ./main
 * First run (with debug info):
 * 1 2 3 4 5
 *
 * Iterator version:
 * 1 2 3 4 5
 */
