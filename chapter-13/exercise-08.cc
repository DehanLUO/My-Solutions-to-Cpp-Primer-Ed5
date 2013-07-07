/*
 * Exercise 13.8: Write the assignment operator for the HasPtr class from
 * exercise 13.5 in § 13.1.1 (p. 499). As with the copy constructor, your
 * assignment operator should copy the object to which ps points.
 */

#include <iostream>  // std::cout
#include <string>    // std::string

class HasPtr {
 public:
  // Constructor
  HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}

  // Copy constructor
  HasPtr(const HasPtr& other) : ps(new std::string(*other.ps)), i(other.i) {}

  ~HasPtr() {
    delete ps;  // Free allocated memory
  }

  /**
   * @brief Copy-assignment operator
   * @param rhs The HasPtr object to copy from
   * @return Reference to this object
   *
   * Key characteristics:
   * 1. Handles self-assignment
   * 2. Performs deep copy of string data
   * 3. Preserves exception safety
   * 4. Returns *this for chaining
   */
  HasPtr& operator=(const HasPtr& rhs) {
    // 1. Check for self-assignment
    if (this != &rhs) {
      // 2. Create new string before deleting old one (exception safety)
      std::string* temp_ps = new std::string(*rhs.ps);

      // 3. Delete old string
      delete ps;

      // 4. Copy data
      ps = temp_ps;
      i = rhs.i;
    }

    // 5. Return reference to this object
    return *this;
  }

  // Utility function to demonstrate the copy
  void Print() const {
    std::cout << "HasPtr @" << this << " {\n"
              << "  ps @" << ps << ": " << *ps << ",\n"
              << "  i: " << i << "\n"
              << "}\n";
  }

 private:
  std::string* ps;
  int i;
};

int main() {
  HasPtr hp1("Hello");
  HasPtr hp2("World");

  std::cout << "Before assignment:\n";
  hp1.Print();
  hp2.Print();

  hp1 = hp2;  // Test normal assignment
  std::cout << "\nAfter assignment:\n";
  hp1.Print();
  hp2.Print();

  hp1 = hp1;  // Test self-assignment
  std::cout << "\nAfter self-assignment:\n";
  hp1.Print();

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-08.cc && ./main
 * Before assignment:
 * HasPtr @0x7ff7bc010c48 {
 *   ps @0x6000013f51a0: Hello,
 *   i: 0
 * }
 * HasPtr @0x7ff7bc010c10 {
 *   ps @0x6000013f51c0: World,
 *   i: 0
 * }
 *
 * After assignment:
 * HasPtr @0x7ff7bc010c48 {
 *   ps @0x6000013f51e0: World,
 *   i: 0
 * }
 * HasPtr @0x7ff7bc010c10 {
 *   ps @0x6000013f51c0: World,
 *   i: 0
 * }
 *
 * After self-assignment:
 * HasPtr @0x7ff7bc010c48 {
 *   ps @0x6000013f51e0: World,
 *   i: 0
 * }
 */
