/*
 * Exercise 7.25: Can Screen safely rely on the default versions of copy and
 * assignment? If so, why? If not, why not?
 */

#include <iostream>  // std::cout

#include "exercise-24.h"  // Screen

/*
 * The Screen class can SAFELY rely on the default versions of:
 * - Copy constructor
 * - Copy assignment operator
 *
 * Rationale:
 * 1. All data members have value semantics:
 *    - std::string (contents_) manages its own memory and supports deep copy
 *    - cursor_, height_, width_ are primitive types, trivially copyable
 *
 * 2. No resource ownership or invariants:
 *    - No raw pointers, dynamic allocation, or file handles
 *    - No invariants that require custom copy logic
 *
 * Therefore, the synthesized versions perform memberwise copy correctly.
 */
int main() {
  Screen original(1, 1, 'y');

  // Default copy operations
  Screen copy1(original);   // Copy constructor
  Screen copy2 = original;  // Copy assignment

  // All copies are independent:
  original.Move(0, 0).Set('X');
  copy1.Move(0, 0).Set('Y');

  original.Display(std::cout);
  copy1.Display(std::cout);

  return 0;
}

/* $ g++ -o main chapter-07/exercise-25.cc
 * Xy
 * yy
 * Yy
 * yy
 */
