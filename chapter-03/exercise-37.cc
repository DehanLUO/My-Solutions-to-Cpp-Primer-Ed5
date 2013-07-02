/*
 * Exercise 3.37: What does the following program do?
 *     const char ca[] = {'h', 'e', 'l', 'l', 'o'};
 *     const char *cp = ca;
 *     while (*cp) {
 *       cout << *cp << endl;
 *       ++cp;
 *     }
 */

#include <iostream>  // std::cout

int main() {
  // Creates a character array `ca` with 5 letters
  const char ca[] = {'h', 'e', 'l', 'l', 'o'};
  // const char ca[] = {'h','e','l','l','o','\0'};  // Proper C-string

  // Uses pointer cp to iterate through `ca`
  const char* cp = ca;

  /*
   * The loop `while(*cp)` expects a null terminator to stop
   * But `ca` lacks a '\0'
   * It will keep reading past the array bounds (undefined behaviour)
   */

  // Prints each character until it finds a null terminator ('\0')
  while (*cp) {
    std::cout << *cp << std::endl;
    ++cp;
  }

  return 0;  // Indicate successful
}

/*
 * g++ -o main chapter-03/exercise-36.cc && ./main
 * h
 * e
 * l
 * l
 * o
 * SOME GARBAGE OUTPUTS
 */