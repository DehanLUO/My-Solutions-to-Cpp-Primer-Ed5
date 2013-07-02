/*
 * Exercise 2.8: Using escape sequences, write a program to print 2M followed by
 * a newline. Modify the program to print 2, then a tab, then an M, followed by
 * a newline.
 */

#include <iostream>  // std::cout

int main() {
  /*
   * \x32 -> hexadecimal escape sequence for '2'
   * \x4d -> hexadecimal escape sequence for 'M'
   * \012 -> octal escape sequence for newline ('\n')
   */
  std::cout << "\x32\x4d\012";

  /*
   * \62 -> octal escape sequence for '2'
   * \t -> escape sequence for horizontal tab
   * \n -> escape sequence for newline
   */
  std::cout << "\62\tM\n";

  return 0;
}

/*
 * $ g++ -o main exercise-08.cc && ./main
 * 2M
 * 2       M
 */
