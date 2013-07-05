/*
 * Exercise 9.30: What, if any, restrictions does using the version of resize
 * that takes a single argument place on the element type?
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

class DefaultConstructible {
 public:
  DefaultConstructible() {  // Default constructor available
    std::cout << "Default constructed\n";
  }
};

class NonDefaultConstructible {
 public:
  explicit NonDefaultConstructible(int x) {}  // No default constructor
};

int main() {
  // Works - int is default constructible (initializes to 0)
  std::vector<int> v1;
  v1.resize(10);  // Creates 10 zeros

  // Works - DefaultConstructible has default constructor
  std::vector<DefaultConstructible> v2;
  v2.resize(5);  // Calls default constructor 5 times

  // Fails to compile - no default constructor
  std::vector<NonDefaultConstructible> v3;
  // v3.resize(5);  // Error: no matching constructor

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-30.cc && ./main
 * Default constructed
 * Default constructed
 * Default constructed
 * Default constructed
 * Default constructed
 */
