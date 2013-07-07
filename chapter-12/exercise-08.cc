/*
 * Exercise 12.8: Explain what if anything is wrong with the following function.
 *     bool b() {
 *       int* p = new int;
 *       // ...
 *       return p;
 *     }
 */

/*
 * Issues:
 * 1. Type mismatch - returns int* but declared to return bool
 * 2. Memory leak - allocated int is never deleted
 * 3. Implicit pointer-to-bool conversion may mask real errors
 */

#include <memory>  // std::unique_ptr

// Problematic function as given
bool b() {
  int* p = new int;  // Allocates memory
  // ... (no delete)
  return p;  // Converts pointer to bool
}

int main() {
  // Original problematic usage
  bool result = b();  // Leaks memory, misleading return

  return 0;
}
