/*
 * Exercise 13.3: What happens when we copy a StrBlob? What about StrBlobPtrs?
 */

#include <iostream>  // std::cout

#include "../chapter-12/exercise-22.h"  // StrBlob, StrBlobPtr

/**
 * @brief Behavior when copying a StrBlob object
 *
 * The StrBlob class uses shared_ptr to manage its underlying vector.
 * When copied:
 * 1. The shared_ptr data_ is copied (reference count increases)
 * 2. Both objects now share the same underlying vector
 * 3. Modifications through one object affect the other
 *
 * This is a shallow copy - no new vector is allocated
 */
void DemonstrateStrBlobCopy() {
  StrBlob blob1({"apple", "banana", "cherry"});
  StrBlob blob2 = blob1;  // Copy occurs here

  // Both objects share the same data
  blob1.PushBack("date");
  std::cout << blob2.Back();  // Outputs "date"
}

/**
 * @brief Behavior when copying a StrBlobPtr object
 *
 * StrBlobPtr contains:
 * 1. A weak_ptr (wptr_) tracking the vector
 * 2. An index (curr_) indicating position
 *
 * When copied:
 * 1. The weak_ptr is copied (no effect on reference count)
 * 2. The current index is copied
 * 3. Both pointers track the same StrBlob but independently
 */
void DemonstrateStrBlobPtrCopy() {
  StrBlob blob({"apple", "banana", "cherry"});
  StrBlobPtr ptr1(blob);
  StrBlobPtr ptr2 = ptr1;  // Copy occurs here

  ptr1.Incr();                // Only affects ptr1
  std::cout << ptr1.Deref();  // "banana"
  std::cout << ptr2.Deref();  // "apple" (unchanged)
}
