/*
 * Exercise 2.11: Explain whether each of the following is a declaration or a
 * definition:
 *     (a) extern int ix = 1024;
 *     (b) int iy;
 *     (c) extern int iz
 */

#include <iostream>  // std::cout

extern int ix = 1024;  // define and initialized to 1024
int iy;                // define and zero-initialized to 0
extern int iz;         // declaration

int main() {
  std::cout << "ix: " << ix << '\n'   //
            << "iy: " << iy << '\n';  //

  /*
   * The statement `extren int iz;` is a declaration, so if `iz` is never
   * defined in any translation unit, the linker will fail with an "undefined
   * reference" error when `iz` is used without adding a definition.
   */
  // std::cout << iz;

  return 0;
}

/*
 * $ g++ -o main exercise-11.cc && ./main
 * exercise-11.cc:11:12: warning: 'extern' variable has an initializer [-Wextern-initializer]
 *    11 | extern int ix = 1024;  // define and initialized to 1024
 *       |            ^
 * 1 warning generated.
 * ix: 1024
 * iy: 0
 */