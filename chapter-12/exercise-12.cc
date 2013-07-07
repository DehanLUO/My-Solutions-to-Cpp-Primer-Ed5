/*
 * Exercise 12.12: Using the declarations of p and sp explain each of the
 * following calls to process. If the call is legal, explain what it does. If
 * the call is illegal, explain why:
 *     auto p = new int();
 *     auto sp = make_shared<int>();
 *     (a) process(sp);
 *     (b) process(new int());
 *     (c) process(p);
 *     (d) process(shared_ptr<int>(p));
 */

#include <iostream>  // std::cout
#include <memory>    // std::shared_ptr

void process(std::shared_ptr<int> ptr) {
  // Use ptr - refcount increased during this function
  std::cout << "Inside process: use_count = " << ptr.use_count() << "\n";
}  // ptr destroyed here - refcount decreased

int main() {
  auto p = new int(42);              // Raw pointer
  auto sp = std::shared_ptr<int>();  // Shared pointer

  /*
   * Legal: Proper shared ownership transfer
   * Creates a copy of sp (use_count increases from 1->2)
   * Safely shares ownership of the managed integer
   * When process ends, use_count decrease from 2->1
   * Recommended way to pass shared pointers
   */
  process(sp);

  /*
   * Illegal: Compile-time error
   * Cannot implicitly convert raw pointer to shared_ptr
   */
  // process(new int());

  /*
   * Illegal: Compile-time error
   * Same issue as (b)
   */
  // process(p);

  /*
   * Legal, bug dangerous
   * It creates a new shared_ptr from raw pointer p
   * Major risk: original p remains as unmanaged raw pointer
   * - Double deletion if p is later deleted
   * - Memory leaks if shared_ptr is the only deleter.
   */
  process(std::shared_ptr<int>(p));
  // Never use p again!

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-12.cc && ./main
 * Inside process: use_count = 0
 * Inside process: use_count = 1
 */
