/*
 * Exercise 4.10: Write the condition for a while loop that would read ints from
 * the standard input and stop when the value read is equal to 42.
 */

#include <iostream>  // std::cin, std::cout

/**
 * @brief Reads integers from input until 42 is encountered
 */
void ReadUntilFortyTwo() {
  int val = 0;

  // Loop condition breakdown:
  // 1. std::cin >> val - Attempts to read an integer
  // 2. val != 42    - Continues while read value isn't 42
  while (std::cin >> val && val != 42) {
    std::cout << "Read: " << val << " (continue until 42)\n";
  }
  std::cout << "Terminated on reading 42\n";
}

int main() {
  // Prompt user and begin reading
  std::cout << "Enter integers (stop at 42):\n";
  ReadUntilFortyTwo();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-10.cc && ./main
 * Enter integers (stop at 42):
 * 21
 * Read: 21 (continue until 42)
 * 42
 * Terminated on reading 42
 */