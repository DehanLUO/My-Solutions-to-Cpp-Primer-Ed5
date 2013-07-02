/*
 * Exercise 4.7: What does overflow mean? Show three expressions that will
 * overflow.
 */

#include <bitset>    // std::bitset
#include <climits>   // INT_MAX, INT_MIN
#include <iomanip>   // std::setw, std::setfill
#include <iostream>  // std::cout

/**
 * @brief Prints the memory representation of a value in multiple formats.
 *
 * This function displays the binary, hexadecimal, and byte-level representation
 * of any given value. It is particularly useful for understanding how data is
 * stored in memory and for examining overflow/underflow behaviour.
 *
 * @tparam T The type of the value being examined (automatically deduced)
 * @param name Descriptive name for the value being printed
 * @param value The actual value to examine in memory
 *
 * Example:
 * @code
 * int x = 42;
 * PrintMemory("Sample integer", x);
 * @endcode
 *
 * @note For signed integers, overflow behaviour is undefined in C++.
 *       The memory representation shown is architecture-dependent.
 */
template <typename T>
void PrintMemory(const char* name, T value) {
  // Output the value's name and decimal representation
  std::cout << name << " (value=" << value << "):\n";

  // Binary representation (all bits shown for the type)
  std::cout << "  Binary: " << std::bitset<sizeof(T) * 8>(value) << '\n';

  // Hexadecimal representation (full width with leading zeros)
  std::cout << "  Hex: 0x" << std::hex << std::setfill('0')
            << std::setw(sizeof(T) * 2) << value << std::dec << '\n';

  // Individual bytes in memory (shows endianness)
  std::cout << "  Bytes: ";
  const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
  for (size_t idx = 0; idx < sizeof(T); ++idx) {
    std::cout << std::setw(3) << static_cast<unsigned>(bytes[idx]) << ' ';
  }
  std::cout << "\n\n";
}

int main() {
  /*
   * OVerflow occurs when a value exceeds the storage capacity of its type,
   * causing it to wrap around to the opposite end.
   */

  // Example 1: Integer overflow
  int a = INT_MAX;
  PrintMemory("a (INT_MAX)", a);
  PrintMemory("a + 1 (overflow)", a + 1);

  // Example 2: Integer underfolw
  int b = INT_MIN;
  PrintMemory("b (INT_MIN)", b);
  PrintMemory("b - 1 (underflow)", b - 1);

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-07.cc && ./main
 * a (INT_MAX) (value=2147483647):
 *   Binary: 01111111111111111111111111111111
 *   Hex: 0x7fffffff
 *   Bytes: 255 255 255 127
 *
 * a + 1 (overflow) (value=-2147483648):
 *   Binary: 10000000000000000000000000000000
 *   Hex: 0x80000000
 *   Bytes: 000 000 000 128
 *
 * b (INT_MIN) (value=-2147483648):
 *   Binary: 10000000000000000000000000000000
 *   Hex: 0x80000000
 *   Bytes: 000 000 000 128
 *
 * b - 1 (underflow) (value=2147483647):
 *   Binary: 01111111111111111111111111111111
 *   Hex: 0x7fffffff
 *   Bytes: 255 255 255 127
 *
 */