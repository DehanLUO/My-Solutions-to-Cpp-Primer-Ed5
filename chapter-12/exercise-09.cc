/*
 * Exercise 12.9: Explain what happens in the following code:
 *     int *q = new int(42), *r = new int(100);
 *     r = q;
 *     auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
 *     r2 = q2;
 */

#include <iostream>  // std::cout
#include <memory>    // std::make_shared

int main() {
  // Raw pointer version
  int *q = new int(42);   // Allocation 1: q points to int(42)
  int *r = new int(100);  // Allocation 2: r points to int(100)

  r = q;  // Memory Leak!
  /*
   * What happens:
   * 1. r now points to same memory as q (int(42))
   * 2. The original int(100) becomes orphaned - no way to access or delete it
   * 3. Memory leak occurs
   */

  // Clean up remaining allocation
  delete q;  // Must manually delete since we used raw pointers
  // delete r; // Would be double-delete - dangerous!

  // Smart pointer version
  auto q2 = std::make_shared<int>(42);   // Allocation 1: refcount = 1
  auto r2 = std::make_shared<int>(100);  // Allocation 2: refcount = 1

  std::cout << "q2.use_count(): " << q2.use_count() << '\n';

  r2 = q2;  // Proper memory management

  std::cout << "q2.use_count(): " << q2.use_count() << '\n';

  /*
   * What happens:
   * 1. r2 now shares ownership with q2 (both point to int(42))
   * 2. r2's original int(100) is automatically deleted (refcount drops to 0)
   * 3. Both pointers now point to int(42), refcount = 2
   */

  return 0;
  /*
   * At scope exit:
   * - q2 and r2 are destroyed
   * - Refcount for int(42) drops to 0
   * - Memory is automatically freed
   */
}

/*
 * $ g++ -o main chapter-12/exercise-09.cc && ./main
 * q2.use_count(): 1
 * q2.use_count(): 2
 */
