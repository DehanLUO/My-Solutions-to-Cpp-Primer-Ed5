/*
 * Exercise 4.28: Write a program to print the size of each of the built-in
 * types.
 */

#include <iostream>  // std::cout

#define PRINT_SIZE(T) PrintSize<T>(#T)

/**
 * @brief Prints the size of a type with description
 * @tparam T Type to check
 * @param typeName Human-readable type name
 */
template <typename T>
void PrintSize(const char* type_name) {
  std::cout << "Size of " << type_name << ": " << sizeof(T) << " byte"
            << (sizeof(T) > 1 ? "s" : "") << "\n";
}

int main() {
  // Fundamental arithmetic types
  std::cout << "Fundamental Types:\n";
  PRINT_SIZE(bool);
  PRINT_SIZE(char);
  PRINT_SIZE(signed char);
  PRINT_SIZE(unsigned char);
  PRINT_SIZE(short);
  PRINT_SIZE(unsigned short);
  PRINT_SIZE(int);
  PRINT_SIZE(unsigned int);
  PRINT_SIZE(long);
  PRINT_SIZE(unsigned long);
  PRINT_SIZE(long long);
  PRINT_SIZE(unsigned long long);
  PRINT_SIZE(float);
  PRINT_SIZE(double);
  PRINT_SIZE(long double);
  PRINT_SIZE(wchar_t);
  PRINT_SIZE(char16_t);
  PRINT_SIZE(char32_t);

  // Pointer types
  std::cout << "\nPointer Types:\n";
  PRINT_SIZE(void*);
  PRINT_SIZE(int*);
  PRINT_SIZE(double*);

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-28.cc && ./main
 * Fundamental Types:
 * Size of bool: 1 byte
 * Size of char: 1 byte
 * Size of signed char: 1 byte
 * Size of unsigned char: 1 byte
 * Size of short: 2 bytes
 * Size of unsigned short: 2 bytes
 * Size of int: 4 bytes
 * Size of unsigned int: 4 bytes
 * Size of long: 8 bytes
 * Size of unsigned long: 8 bytes
 * Size of long long: 8 bytes
 * Size of unsigned long long: 8 bytes
 * Size of float: 4 bytes
 * Size of double: 8 bytes
 * Size of long double: 16 bytes
 * Size of wchar_t: 4 bytes
 * Size of char16_t: 2 bytes
 * Size of char32_t: 4 bytes
 *
 * Pointer Types:
 * Size of void*: 8 bytes
 * Size of int*: 8 bytes
 * Size of double*: 8 bytes
 */