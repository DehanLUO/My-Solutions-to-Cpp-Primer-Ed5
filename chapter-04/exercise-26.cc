/*
 * Exercise 4.26: In our grading example in this section, what would happen if
 * we used unsigned int as the type for quiz1?
 */

#include <bitset>    // std::bitset
#include <iostream>  // std::cout

/**
 * @brief Demonstrates the problem with using unsigned int for bit operations
 */
void ExplainUnsignedIntIssue() {
  /*
   * In C++11, the minimum number of bits required for unsigned int is 16 bits,
   * and for unsigned long is 32 bits. These are the shortest binary widths
   * mandated by the standard. However, actual sizes may be larger depending on
   * the platform and compiler implementation.
   */

  // Original safe version with uint32_t (unsigned long)
  uint32_t quiz32 = 0;
  quiz32 |= 1UL << 27;  // Correct - sets bit 27
  std::cout << "Using unsigned long (safe):\n";
  std::cout << "Bit 27 set correctly: " << (quiz32 & (1UL << 27)) << '\n';
  std::cout << "binary: " << std::bitset<32>(quiz32) << "\n\n";

  // Problematic version with uint16_t (unsigned int)
  uint16_t quiz16 = 0;

  std::cout << "Using unsigned int (problematic):\n";
  std::cout << "Size of unsigned: " << sizeof(uint16_t) << " bytes\n";

  // Attempt to set bit 27 (undefined behavior)
  quiz16 |= 1UL << 27;
  std::cout << "Bit 27 value: " << (quiz16 & (1UL << 27)) << "\n";
  std::cout << "Actual stored value: " << quiz16 << "\n";
  std::cout << "binary: " << std::bitset<16>(quiz16) << "\n\n";
}

int main() {
  ExplainUnsignedIntIssue();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-26.cc && ./main
 * Using unsigned log (safe):
 * Bit 27 set correctly: 134217728
 * binary: 00001000000000000000000000000000
 *
 * Using unsigned int (problematic):
 * Size of unsigned: 2 bytes
 * Bit 27 value: 0
 * Actual stored value: 0
 * binary: 0000000000000000
 */