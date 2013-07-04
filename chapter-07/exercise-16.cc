/*
 * Exercise 7.16: What, if any, are the constraints on where and how often an
 * access specifier may appear inside a class definition? What kinds of members
 * should be defined after a public specifier? What kinds should be private?
 */

#include <iostream>  // std::cout

/*
 * Example class showing access specifier best practices
 */
class AccessDemo {
 public:
  /*
   * Public members typically include:
   * 1. Constructor/destructor interfaces
   * 2. Public API methods
   * 3. Constants needed by users
   */

  /**
   * @brief Constructs a new AccessDemo object
   */
  AccessDemo() : private_data_(0) {}

  /**
   * @brief Public interface method
   * @return Important calculated value
   */
  int GetCalculatedValue() const {
    // Delegates to private implementation
    return PrivateCalculation();
  }

  /**
   * @brief Public constant available to all users
   */
  static const int kPublicConstant = 100;

 private:
  /*
   * Private members typically include:
   * 1. Implementation details
   * 2. Internal state variables
   * 3. Helper methods
   */

  /**
   * @brief Performs the actual calculation
   * @return Computed result
   */
  int PrivateCalculation() const { return private_data_ * kPrivateMultiplier; }

  int private_data_;                        // Internal state
  static const int kPrivateMultiplier = 2;  // Implementation detail
};

int main() {
  /*
   * Key rules demonstrated:
   * 1. Access specifiers can appear anywhere in class definition
   * 2. Can alternate between specifiers as needed
   * 3. Effect persists until another specifier appears
   */

  AccessDemo demo;
  std::cout << "Public value: " << demo.GetCalculatedValue() << '\n';
  std::cout << "Public constant: " << AccessDemo::kPublicConstant << '\n';

  // demo.private_data_; // Error: private member
  // demo.PrivateCalculation(); // Error: private method

  return 0;
}

/* $ g++ -o main chapter-07/exercise-16.cc && ./main
 * Public value: 0
 * Public constant: 100
 */
