/*
 * Exercise 13.57: What if we defined sorted as:
 *     Foo Foo::sorted() const& { return Foo(*this).sorted(); }
 */

#ifndef CHAPTER_13_EXERCISE_57_H_
#define CHAPTER_13_EXERCISE_57_H_

#include <algorithm>  // std::sort
#include <vector>     // std::vector

class Foo {
 public:
  Foo sorted() && {
    std::sort(data_.begin(), data_.end());
    return *this;
  }  // may run on modifiable rvalues

  //   Foo sorted() const& {
  //     Foo ret(*this);                                 // make a copy
  //     std::sort(ret.data_.begin(), ret.data_.end());  // sort the copy
  //     return ret;
  //   }  // may run on any kind of Foo

  /*
   * 1. Foo(*this) creates a temporary (rvalue)
   * 2. Member functions on temporaries prefer rvalue overloads
   *    Call the move-qualified sorted() &&
   */
  Foo sorted() const& { return Foo(*this).sorted(); }

 private:
  std::vector<int> data_;
};

#endif  // CHAPTER_13_EXERCISE_57_H_
