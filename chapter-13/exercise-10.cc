/*
 * Exercise 13.10: What happens when a StrBlob object is destroyed? What about a
 * StrBlobPtr?
 */

#include "../chapter-12/exercise-22.h"  // StrBlob, StrBlobPtr

int main() {
  /*
   * 1. Destructor Execution:
   *    - The compiler-generated destructor is called
   *    - It destroys all members in reverse declaration order
   * 2. Shared Pointer Cleanup:
   *    - The shared_ptr<vector<string>> data_ memeber is destroyed
   *    - The shared pointer's destructor:
   *      - Decrements the reference count
   *      - If count reaches 0 (last owner):
   *        - Destroys the managed vector<string>
   *        - The vector's destructor destroys all string elements
   *        - Frees the vector's memory
   * 3. Memory Management:
   *      // Equivalent to compiler-generated destructor:
   *      ~StrBlob() {
   *        data_.~shared_ptr();  // shared_ptr destructor handles cleanup
   *      }
   */
  {
    StrBlob blob({"apple", "banana"});  // Constructor called

    // ... use blob ...
  }  // blob destroyed here

  /*
   * 1. Destructor Execution:
   *    - The compiler-generated destructor is called
   *    - Destroys members in reverse declaration order
   * 2. Weak Pointer Cleanup:
   *    - The weak_ptr<vector<string>> wptr_ member is destroyed
   *    - The weak pointer's destructor:
   *      - Removes that weak reference
   *      - Does not affect the reference count
   *      - Does not destroy the managed object
   * 3. Current Index Cleanup:
   *    - The size_t curr_ member is destroyed (no action needed)
   * 4. No Impact On StrBlob:
   *    - Destroying StrBlobPtr has no effect on the StrBlob it points to
   *    - The underlying vector remains intact if StrBlob still exists
   */
  {
    StrBlob blob({"apple", "banana"});
    StrBlobPtr ptr(blob);  // Constructor called

    // ... use ptr ...
  }  // ptr destroyed here

  return 0;
}
