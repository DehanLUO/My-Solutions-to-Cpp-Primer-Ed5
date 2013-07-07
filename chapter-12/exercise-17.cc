/*
 * Exercise 12.17: Which of the following unique_ptr declarations are illegal or
 * likely to result in subsequent program error? Explain what the problem is
 * with each one.
 *     int ix = 1024, *pi = &ix, *pi2 = new int(2048);
 *     typedef unique_ptr<int> IntP;
 *     (a) IntP p0(ix);            (b) IntP p1(pi);
 *     (c) IntP p2(pi2);           (d) IntP p3(&ix);
 *     (e) IntP p4(new int(2048)); (f) IntP p5(p2.get());
 */

#include <iostream>
#include <memory>  // std::unique_ptr

int main() {
  int ix = 1024, *pi = &ix, *pi2 = new int(2048);
  typedef std::unique_ptr<int> IntP;

  /*
   * Illegal: Attempting to construct unique_ptr from int value
   * Error: No matching constructor for initialization
   * Fix: Must pass pointer, not integer
   */
  // IntP p0(ix);

  /*
   * Legal but risky:
   * - Constructs unique_ptr from stack address (&ix)
   * - Will attempt to delete stack memory when p1 goes out of scope
   * - Results in undefined behavior
   * Fix: Never manage stack memory with smart pointers
   */
  // IntP p1(pi);

  /*
   * Legal but risky:
   * - Takes ownership of heap-allocated int(2048)
   * - Same issue as (b)
   */
  // IntP p2(pi2);

  /*
   * Legal but risky:
   * - Same problem as (b)
   * - Attempts to delete stack variable ix
   * - Results in undefined behavior
   * Fix: Never take ownership of stack addresses
   */
  // IntP p3(&ix);

  /*
   * Perfectly legal and correct:
   * - Direct ownership of newly allocated heap memory
   * - No dangling pointer issues
   * - Preferred way to initialize unique_ptr
   */
  // IntP p4(new int(2048));

  /*
   * Illegal and dangerous:
   * - Attempts to create second unique_ptr from same raw pointer
   * - Will cause double deletion
   * - Error: Call to implicitly-deleted copy constructor
   * Fix: Use move semantics: IntP p5(std::move(p2))
   */
  // IntP p5(p2.get());

  delete pi2;  // Manual cleanup

  return 0;
}
