/*
 * Exercise 12.13: What happens if we execute the following code?
 *     auto sp = make_shared<int>();
 *     auto p = sp.get();
 *     delete p;
 */

#include <memory>  // std::shared_ptr

int main() {
  auto sp = std::make_shared<int>();  // proper shared_ptr creation
  auto p = sp.get();                  // extracts raw pointer
  delete p;                           // manually deletes the memory

  return 0;
  /*
   * When sp goes out of scope, it will attempt to delete the same memory again
   * This is undefined behaviour (typically crashes the program)
   */
}

/*
 * $ g++ -o main chapter-12/exercise-13.cc && ./main
 * main(13442,0x7ff8493fadc0) malloc: *** error for object 0x6000015811b8: pointer being freed was not allocated
 * main(13442,0x7ff8493fadc0) malloc: *** set a breakpoint in malloc_error_break to debug
 * [1]    13442 abort      ./main
 */
