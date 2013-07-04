/*
 * Exercise 7.45: What if we defined the vector in the previous execercise to
 * hold objects of type C?
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

class NoDefault {
 public:
  /**
   * @brief Constructs NoDefault with specified value
   * @param val Initialization value
   */
  explicit NoDefault(int val) : value_(val) {}

  int GetValue() const { return value_; }

 private:
  int value_;
};

class C {
 public:
  /**
   * @brief Default constructs C with initialized NoDefault member
   * @note Uses in-class member initializer for NoDefault
   */
  C() : member_(42) {}  // Arbitrarily chosen default value

  /**
   * @brief Gets the NoDefault member's value
   * @return Current value of the member
   */
  int GetMemberValue() const { return member_.GetValue(); }

 private:
  NoDefault member_;
};

int main() {
  /*
   * Legal because:
   * 1. C provides its own default constructor
   * 2. C's constructor properly initializes NoDefault member
   * 3. Each vector element will be value-initialized using C::C()
   */
  std::vector<C> vec(3);

  for (const auto& item : vec) {
    std::cout << item.GetMemberValue() << '\n';
  }

  return 0;
}

/* $ g++ -o main chapter-07/exercise-45.cc && ./main
 * 42
 * 42
 * 42
 */
