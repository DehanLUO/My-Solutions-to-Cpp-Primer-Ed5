/*
 * Exercise 13.51: Although unique_ptrs cannot be copied, in § 12.1.5 (p. 471)
 * we wrote a clone function that returned a unique_ptr by value. Explain why
 * that function is legal and how it works.
 */

/*
 * Explanation of legality:
 *
 * 1. Move Semantics:
 *    - unique_ptr has a deleted copy constructor but implements move semantics
 *    - When returning by value, the compiler performs move operations
 * 2. Return Value Optimization (RVO):
 *    - Modern compilers elide copies/moves in return statements
 *    - The object is constructed directly in the caller's context
 *
 * Both versions shown are functionally equivalent:
 * - First version uses explicit temporary
 * - Second version uses named return value optimization (NRVO)
 *
 * The unique_ptr ownership is transferred to the caller through:
 * 1. Implicit move construction (if RVO doesn't occur)
 * 2. Direct construction (when RVO is applied)
 */

#include <memory>  // std::unique_ptr

std::unique_ptr<int> clone(int p) {
  // ok: explicitly create a unique_ptr<int> from int*
  return std::unique_ptr<int>(new int(p));

  // alternatively, return a copy of a local object
  std::unique_ptr<int> ret(new int(p));
  return ret;
}
