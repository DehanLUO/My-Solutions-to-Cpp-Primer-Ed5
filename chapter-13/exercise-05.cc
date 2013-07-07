/*
 * Exercise 13.5: Given the following sketch of a class, write a copy
 * constructor that copies all the members. Your constructor should dynamically
 * allocate a new string (§ 12.1.2, p. 458) and copy the object to which ps
 * points, rather than copying ps itself.
 *     class HasPtr {
 *      public:
 *       HasPtr(const std::string &s = std::string()) :
 *           ps(new std::string(s)), i(0) {}
 *      private:
 *       std::string *ps;
 *       int i;
 *     };
 */

#include <iostream>  // std::cout
#include <string>    // std::string

class HasPtr {
 public:
  HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}

  /**
   * @brief Copy constructor that performs deep copy
   * @param other The HasPtr object to copy from
   *
   * Key characteristics:
   * 1. Allocates new memory for the string
   * 2. Copies the string content, not just the pointer
   * 3. Copies all other members (i in this case)
   * 4. Maintains exception safety
   */
  HasPtr(const HasPtr& other) : ps(new std::string(*other.ps)), i(other.i) {}

  ~HasPtr() {
    delete ps;  // Free allocated memory
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
  // Demonstrate the copy constructor
  HasPtr original("Hello World");
  HasPtr copy = original;  // Copy constructor invoked here

  // Verify they're truly independent
  original.Print();
  copy.Print();

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-05.cc && ./main
 * HasPtr @0x7ff7bcfabc48 {
 *   ps @0x6000023d8000: Hello World,
 *   i: 0
 * }
 * HasPtr @0x7ff7bcfabc10 {
 *   ps @0x6000023d8020: Hello World,
 *   i: 0
 * }
 */
