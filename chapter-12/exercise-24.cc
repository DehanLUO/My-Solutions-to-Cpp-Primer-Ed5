/*
 * Exercise 12.24: Write a program that reads a string from the standard input
 * into a dynamically allocated character array. Describe how your program
 * handles varying size inputs. Test your program by giving it a string of data
 * that is longer than the array size you’ve allocated.
 */

#include <cstring>    // strlen, strcpy
#include <iostream>   // std::cin, std::cout
#include <stdexcept>  // std::runtime_error

/**
 * @brief Reads input into dynamically allocated buffer with safe expansion
 * @param initial_size Starting buffer size (must be > 0)
 * @return char* Pointer to null-terminated string
 * Time Complexity: O(n) where n is input length
 * Space Complexity: O(n) for final buffer
 */
char* ReadDynamicString(size_t initial_size) {
  if (initial_size == 0) {
    throw std::runtime_error("Initial size must be positive");
  }

  size_t current_size = initial_size;
  char* buffer = new char[current_size];
  size_t position = 0;

  /*
   * Using cin.get() rather than >> operator to:
   * 1. Preserve whitespace characters
   * 2. Allow precise buffer size tracking
   * 3. Enable growth strategy implementation
   */
  while (std::cin.get(buffer[position])) {
    if (buffer[position] == '\n') {
      buffer[position] = '\0';
      break;
    }

    position++;

    /*
     * Growth strategy: When remaining space drops below 10%,
     * double the buffer size to maintain O(1) amortized time
     * for each insertion operation
     */
    if (position >= current_size - 1) {
      size_t new_size = current_size * 2;
      char* new_buffer = new char[new_size];

      // Copy existing content
      std::strcpy(new_buffer, buffer);
      delete[] buffer;
      buffer = new_buffer;
      current_size = new_size;

      /*
       * Safety consideration: Practical limit prevents
       * excessive memory allocation from malicious input
       */
      if (current_size > 40) {
        delete[] buffer;
        throw std::runtime_error("Input exceeds safe size limit");
      }
    }
  }

  return buffer;
}

int main() {
  const size_t initial_buffer_size = 10;  // Purposely small for testing

  /*
   * Testing protocol:
   * 1. Normal case (short string)
   * 2. Boundary case (exact buffer size)
   * 3. Overflow case (large string)
   */
  std::cout << "Enter test string (will demonstrate growth):\n";
  char* result = ReadDynamicString(initial_buffer_size);
  std::cout << "Captured string: " << result << '\n';

  /*
   * Memory management note:
   * Caller becomes owner of the pointer and must eventually call delete[] to
   * prevent leaks
   */
  delete[] result;

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-24.cc && ./main
 * Enter test string (will demonstrate growth):
 * The quick brown fox jumps over the laz
 * Captured string: The quick brown fox jumps over the laz
 * $ ./main
 * Enter test string (will demonstrate growth):
 * The quick brown fox jumps over the lazy
 * libc++abi: terminating due to uncaught exception of type std::runtime_error: Input exceeds safe size limit
 * [1]    29118 abort      ./main
 */
