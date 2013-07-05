/*
 * Exercise 9.37: Why don’t list or array have a capacity member?
 */

#include <array>     // std::arrau
#include <iostream>  // std::cout
#include <list>      // std::list
#include <vector>    // std::vector

/**
 * @brief Demonstrates capacity behavior across different containers
 */
void CompareContainerStorage() {
  /*
   * In c++, the capacity() member function is provided by containers like
   * std::vector to indicate the amount of storage that has been allocated in
   * advance, beyond the current number of elements held by the container. This
   * is particularly useful for optimizing performance during dynamic resizing.
   */
  std::vector<int> vec = {1, 2, 3};
  std::cout << "Vector:\n";
  std::cout << "  Size: " << vec.size() << "\n";
  std::cout << "  Capacity: " << vec.capacity() << "\n\n";

  /*
   * A std::list is a doubly-linked list. Its elements are not stored in
   * contiguous memory; rather, each element is dynamically allocated as a
   * separate node, linked to its neighbours throuth pointers.
   * - Since the elements are not stored in a single contiguous block of memory,
   *   the concept of a pre-allocated buffer does not apply.
   * - Consequently, a std::list does not need, and cannot benefit from, the
   *   notion of capacity.
   * - Adding or removing elements does not involve memory reallocation in the
   *   same way that it does with a std::vector.
   */
  std::list<int> lst = {1, 2, 3};
  std::cout << "List:\n";
  std::cout << "  Size: " << lst.size() << "\n";
  // lst.capacity() // Doesn't exist - compile error

  /*
   * In contrast, std::array<T, N> is a container that wraps a fixed-size array
   * of N elements. Its storage is:
   * - Contiguous: Like std::vector, the elements are laid out sequentially in
   *   memory.
   * - Static: The size is determined at compile time and cannot be changed at
   *   runtime.
   * Given that the number of elements is fixed and known at compile time, there
   * is no distinction between the container's size and its capacity - both are
   * always equal to N.
   * - Therefore, a separate capacity() member would serve no additional
   *   purpose.
   * - The size() member is sufficient for all practical uses.
   */
  std::array<int, 3> arr = {1, 2, 3};
  std::cout << "Array:\n";
  std::cout << "  Size: " << arr.size() << "\n";
  // arr.capacity() // Doesn't exist - compile error
}

int main() {
  CompareContainerStorage();

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-37.cc && ./main
 * Vector:
 *   Size: 3
 *   Capacity: 3
 *
 * List:
 *   Size: 3
 * Array:
 *   Size: 3
 */
