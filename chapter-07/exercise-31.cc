/*
 * Exercise 7.31: Define a pair of classes X and Y, in which X has a pointer to
 * Y, and Y has an object of type X.
 */

#include <ios>       // std::boolalpha
#include <iostream>  // std::cout

// Forward declaration of Y so X can declare Y*
class Y;

class X {
 private:
  Y* y_ptr_;  // Pointer to Y (incomplete type is fine for pointers)

 public:
  /**
   * @brief Construct a new X object
   * @param y Pointer to associated Y object (can be nullptr)
   */
  explicit X(Y* y = nullptr) : y_ptr_(y) {}

  /**
   * @brief Set the associated Y object
   * @param y Pointer to Y object
   */
  void SetY(Y* y) { y_ptr_ = y; }

  /**
   * @brief Get the associated Y object
   * @return Y* Pointer to Y object
   */
  Y* GetY() const { return y_ptr_; }
};

class Y {
 private:
  X x_obj_;  // Complete X object (requires full definition of X)

 public:
  /**
   * @brief Construct a new Y object
   * @param x X object to store (default constructed if not provided)
   */
  explicit Y(const X& x = X()) : x_obj_(x) {}

  /**
   * @brief Get the contained X object
   * @return const X& Reference to contained X
   */
  const X& GetX() const { return x_obj_; }

  /**
   * @brief Get mutable reference to contained X object
   * @return X& Reference to contained X
   */
  X& GetX() { return x_obj_; }
};

/*
 * Demonstration of usage:
 * 1. Shows how to create interconnected X and Y objects
 * 2. Demonstrates proper initialization order
 */
int main() {
  Y y1;  // Contains default-constructed X
  X& x1 = y1.GetX();
  x1.SetY(&y1);  // Points to y1

  std::cout << std::boolalpha;

  // Demonstrate the circular relationship
  std::cout << "x1 points to y1? " << (x1.GetY() == &y1) << '\n';
  std::cout << "y1 contains x1? " << (&y1.GetX() == &x1) << '\n';

  return 0;
}

/* $ g++ -o main chapter-07/exercise-31.cc && ./main
 * x1 points to y1? true
 * y1 contains x1? true
 */
