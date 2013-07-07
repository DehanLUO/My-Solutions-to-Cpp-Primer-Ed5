/*
 * Exercise 13.7: What happens when we assign one StrBlob to another? What about
 * StrBlobPtrs?
 */

#include <iostream>  // std::cout

#include "../chapter-12/exercise-22.h"  // StrBlob, StrBlobPtr

int main() {
  StrBlob blob1({"apple", "banana"});
  StrBlobPtr ptr1(blob1);

  StrBlob blob2({"orange"});
  StrBlobPtr ptr2(blob2, 0);

  std::cout << ptr1.Deref() << ", " << ptr2.Deref() << '\n';

  /*
   * Assignment operation. Shared Ownership Transer:
   * - The shared_ptr (data_) in blob1 is assigned the shared_ptr from blob2
   * - Reference count for the underlying vector increases by 1
   * - Original blob1 vector is destroyed if this was the last reference
   */
  blob1 = blob2;

  /*
   * Member-wise assignment:
   * - The weak-ptr (wptr_) is assigned from source to destination
   * - The current index (curr_) is copied
   * - No change in reference counts (weak_ptr does not affect ownership)
   */
  ptr1 = ptr2;

  std::cout << ptr1.Deref() << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-07.cc && ./main
 * apple, orange
 * orange
 */
