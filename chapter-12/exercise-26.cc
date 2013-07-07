/*
 * Exercise 12.26: Rewrite the program on page 481 using an allocator.
 */

#include <cstddef>   // size_t
#include <iostream>  // std::cin, std::cout
#include <memory>    // std::allocator
#include <string>    // std::string

constexpr size_t kN = 10;  // Maximum number of strings to read

int main() {
  std::allocator<std::string> alloc;

  /*
   * Memory allocation phase:
   * 1. allocate() get raw memory (no constructions)
   * 2. Must track constructed objects separately
   */
  std::string *ptr = alloc.allocate(kN);
  std::string *current = ptr;
  std::string str;

  try {
    /*
     * Emergency cleanup if construction fails:
     * Destroy all successfully constructed objects before rethrowing the
     * execption
     */
    while (current != ptr + kN && std::cin >> str) {
      alloc.construct(current++, str);
    }
  } catch (...) {
    while (current != ptr) {
      alloc.destroy(--current);
    }
    alloc.deallocate(ptr, kN);
  }

  const size_t size = current - ptr;  // Number of constructed strings

  /*
   * Usage example:
   * Process all constructed strings
   * Note: &ptr[i] is valid only for i < size
   */
  for (size_t idx = 0; idx < size; ++idx) {
    std::cout << "String " << idx << ": " << ptr[idx] << '\n';
  }

  /*
   * Proper deallocation sequence:
   * 1. destroy() each constructed object
   * 2. deallocate() the memory block
   * Order is critical to prevent leaks
   */
  while (current != ptr) {
    alloc.destroy(--current);
  }
  alloc.deallocate(ptr, kN);

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-26.cc && ./main
 * 1 2 3 4 5 6 7 8 9 10
 * String 0: 1
 * String 1: 2
 * String 2: 3
 * String 3: 4
 * String 4: 5
 * String 5: 6
 * String 6: 7
 * String 7: 8
 * String 8: 9
 * String 9: 10
 */
