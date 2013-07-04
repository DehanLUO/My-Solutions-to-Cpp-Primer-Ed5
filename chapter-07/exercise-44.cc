/*
 * Exercise 7.44: Is the following declaration legal? If not, why not?
 *     vector<NoDefault> vec(10);
 */

#include <vector>  // std::vector

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
   * The vector constructor attempts to value-initialize 10 elements
   * - vector::vector(size_type count) requires default-constructible T
   * - NoDefault lacks default constructor
   * - Results in compilation error
   */
  // std::vector<NoDefault> vec(10);

  return 0;
}
