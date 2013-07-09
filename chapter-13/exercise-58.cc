/*
 * Exercise 13.58: Write versions of class Foo with print statements in their
 * sorted functions to test your answers to the previous two exercises.
 */

#include <algorithm>  // std::sort
#include <iostream>   // std::cout
#include <vector>     // std::vector

class Foo {
 public:
  Foo sorted() && {
    std::cout << "Foo sorted() &&\n";
    std::sort(data_.begin(), data_.end());
    return *this;
  }  // may run on modifiable rvalues

  Foo sorted() const& {
    std::cout << "Foo sorted() const&\n";
    Foo ret(*this);                                 // make a copy
    std::sort(ret.data_.begin(), ret.data_.end());  // sort the copy
    return ret;
  }  // may run on any kind of Foo

  Foo sorted_exercise_56() && {
    std::cout << "Foo sorted_exercise_56() &&\n";
    std::sort(data_.begin(), data_.end());
    return *this;
  }  // may run on modifiable rvalues

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
  Foo sorted_exercise_56() const& {
    static uint16_t count = 0;

    std::cout << "Foo sorted_exercise_56() const&:" << count << "\n";
    if (1 < count++) throw std::logic_error("infinite recursion breakdown");

    Foo ret(*this);  // make a copy
    return ret.sorted_exercise_56();
  }

  Foo sorted_exercise_57() && {
    std::cout << "Foo sorted_exercise_57() &&\n";
    std::sort(data_.begin(), data_.end());
    return *this;
  }  // may run on modifiable rvalues

  /*
   * 1. Foo(*this) creates a temporary (rvalue)
   * 2. Member functions on temporaries prefer rvalue overloads
   *    Call the move-qualified sorted() &&
   */
  Foo sorted_exercise_57() const& {
    std::cout << "Foo sorted_exercise_57() const&\n";
    return Foo(*this).sorted_exercise_57();
  }

  void dump() {
    for (const int num : data_) std::cout << num << ' ';
    std::cout << '\n';
  }

  void push_back(int value) { data_.push_back(value); }

 private:
  std::vector<int> data_;
};

int main() {
  Foo foo;
  foo.push_back(3);
  foo.push_back(2);
  foo.push_back(1);
  foo.dump();

  std::cout << "1. foo.sorted().dump()\n";
  foo.sorted().dump();
  foo.dump();

  try {
    std::cout << "\n2. foo.sorted_exercise_56().dump()\n";
    foo.sorted_exercise_56().dump();
    foo.dump();
  } catch (const std::logic_error& e) {
    std::cout << e.what() << '\n';
  }

  std::cout << "\n3. foo.sorted_exercise_57().dump()\n";
  foo.sorted_exercise_57().dump();
  foo.dump();

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-58.cc && ./main
 * 3 2 1
 * 1. foo.sorted().dump()
 * Foo sorted() const&
 * 1 2 3
 * 3 2 1
 *
 * 2. foo.sorted_exercise_56().dump()
 * Foo sorted_exercise_56() const&:0
 * Foo sorted_exercise_56() const&:1
 * Foo sorted_exercise_56() const&:2
 * infinite recursion breakdown
 *
 * 3. foo.sorted_exercise_57().dump()
 * Foo sorted_exercise_57() const&
 * Foo sorted_exercise_57() &&
 * 1 2 3
 * 3 2 1
 */
