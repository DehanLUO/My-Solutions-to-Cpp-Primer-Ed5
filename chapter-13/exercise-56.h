/*
 * Exercise 13.56: What would happen if we defined sorted as:
 *     Foo Foo::sorted() const& {
 *       Foo ret(*this);
 *       return ret.sorted();
 *     }
 */

#ifndef CHAPTER_13_EXERCISE_56_H_
#define CHAPTER_13_EXERCISE_56_H_

#include <algorithm>  // std::sort
#include <vector>     // std::vector

class Foo {
 public:
  Foo sorted() && {
    std::sort(data_.begin(), data_.end());
    return *this;
  }  // may run on modifiable rvalues

  Foo sorted() const& {
    Foo ret(*this);                                 // make a copy
    std::sort(ret.data_.begin(), ret.data_.end());  // sort the copy
    return ret;
  }  // may run on any kind of Foo

  /*
   * Infinite Recursion Breakdown:
   * 1. When calling on lvalue:
   *    - const& version is selected
   *    - Creates copy 'ret'
   *    - Calls ret.sorted()
   * 2. ret is:
   *    - An lvalue (named object)
   *    - const-qualified (from *this)
   *    - Therefore calls const& version again
   * 3. Process repeats indefinitely:
   *    - New stack frame each call
   *    - No base case
   *    - Eventually crashes
   */
  //   Foo sorted() const& {
  //     Foo ret(*this);  // make a copy
  //     return ret.sorted();
  //   }

 private:
  std::vector<int> data_;
};

#endif  // CHAPTER_13_EXERCISE_56_H_
