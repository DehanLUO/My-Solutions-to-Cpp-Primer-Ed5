/*
 * Exercise 12.11: What would happen if we called process as follows?
 *     process(shared_ptr<int>(p.get()));
 */

#include <iostream>  // std::cout
#include <memory>    // std::shared_ptr

void process(std::shared_ptr<int> ptr) {
  // Use ptr - refcount increased during this function
  std::cout << "Inside process: use_count = " << ptr.use_count() << "\n";
}  // ptr destroyed here - refcount decreased

int main() {
  // Original implementation
  std::shared_ptr<int> p(new int(42));  // refcount = 1

  /*
   * This code demonstrates a critical memory management error that violates c++
   * smart point rules. It creates a new shared_ptr form the raw pointer
   * obtained via p.get(), which leads to undefined behaviour sequence:
   * - p.get() extracts the raw pointer (address of the int)
   * - Constructs a new shared_ptr from this raw pointer
   * - Creates a second, independent reference count
   * Temporary destoryed after process (refcount=0 -> delete memory)
   */
  process(std::shared_ptr<int>(p.get()));
  /*
   * Original p now points to deleted memory (dangling pointer)
   */

  /*
   * Correct version:
   * Shares p's ownership
   */
  // process(std::shared_ptr<int>(p, p.get()));

  return 0;

  /*
   * p's destructor runs (double deletion -> crash)
   */
}

/*
 * $ g++ -o main chapter-12/exercise-11.cc && ./main
 * Inside process: use_count = 1
 * main(12498,0x7ff8493fadc0) malloc: *** error for object 0x600002be4050: pointer being freed was not allocated
 * main(12498,0x7ff8493fadc0) malloc: *** set a breakpoint in malloc_error_break to debug
 * [1]    12498 abort      ./main
 */
