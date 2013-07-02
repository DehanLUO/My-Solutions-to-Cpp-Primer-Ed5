/*
 * Exercise 4.25: What is the value of~’q’ << 6 on a machine with 32-bit ints
 * and 8 bit chars, that uses Latin-1 character set in which ’q’ has the bit
 * pattern 01110001?
 */

#include <bitset>    // std::bitset
#include <iostream>  // std::cout

/**
 * @brief Demonstrates bitwise operation ~'q' << 6 with 32-bit ints
 */
void ExplainBitOperation() {
  // Given parameters:
  // - 32-bit integers
  // - 8-bit chars (Latin-1)
  // - 'q' = 01110001 (0x71)

  char q = 'q';              // 01110001
  int not_q = ~q;            // Bitwise NOT
  int shifted = not_q << 6;  // Left shift 6 positions

  std::cout << "Step-by-step evaluation:\n";
  std::cout << "1. 'q' binary:        " << std::bitset<8>(q) << "\n";
  std::cout << "2. After ~ operation: " << std::bitset<32>(not_q) << "\n";
  std::cout << "3. After << 6:        " << std::bitset<32>(shifted) << "\n";
  std::cout << "Final value (decimal): " << shifted << "\n";
  std::cout << "Final value (hex):     0x" << std::hex << shifted << std::dec
            << "\n";
}

int main() {
  ExplainBitOperation();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-25.cc && ./main
 * Step-by-step evaluation:
 * 1. 'q' binary:        01110001
 * 2. After ~ operation: 11111111111111111111111110001110
 * 3. After << 6:        11111111111111111110001110000000
 * Final value (decimal): -7296
 * Final value (hex):     0xffffe380
 */
