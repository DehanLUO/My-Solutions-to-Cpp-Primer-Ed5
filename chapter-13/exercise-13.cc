/*
 * Exercise 13.13: A good way to understand copy-control members and
 * constructors is to define a simple class with these members in which each
 * member prints its name:
 *     struct X {
 *       X() { std::cout << "X()" << std::endl; }
 *       X(const X&) { std::cout << "X(const X&)" << std::endl; }
 *     };
 * Add the copy-assignment operator and destructor to X and write a program
 * using X objects in various ways: Pass them as nonreference and reference
 * parameters; dynamically allocate them; put them in containers; and so forth.
 * Study the output until you are certain you understand when and why each
 * copy-control member is used. As you read the output, remember that the
 * compiler can omit calls to the copy constructor.
 */

#include <iostream>  // std::cout
#include <vector>    // std::vector

struct X {
  // Default constructor
  X() { std::cout << "X() @" << this << "\n"; }

  // Copy constructor
  X(const X&) { std::cout << "X(const X&) @" << this << "\n"; }

  // Copy assignment operator
  X& operator=(const X&) {
    std::cout << "X& operator=(const X&) @" << this << "\n";
    return *this;
  }

  // Destructor
  ~X() { std::cout << "~X() @" << this << "\n"; }
};

// Function to demonstrate parameter passing
void Val(X x) {}   // Pass by value
void Ref(X& x) {}  // Pass by reference
X Ret() {          // Return by value
  X x;
  return x;
}

int main() {
  std::cout << "=== Direct initialization ===\n";
  X x1;  // Default constructor

  std::cout << "\n=== Copy initialization ===\n";
  X x2 = x1;  // Copy constructor

  std::cout << "\n=== Assignment ===\n";
  X x3;
  x3 = x1;  // Copy assignment

  std::cout << "\n=== Function arguments ===\n";
  Val(x1);  // Copy constructor (parameter)
            // Destructor (parameter when f_val exits)
  Ref(x1);  // No copies

  std::cout << "\n=== Return values ===\n";
  X x4 = Ret();  // May involve copy elision

  std::cout << "\n=== Container operations ===\n";
  std::vector<X> vec;
  vec.push_back(x1);  // Copy constructor (unless moved)

  std::cout << "\n=== Dynamic allocation ===\n";
  X* px = new X(x1);  // Copy constructor
  delete px;          // Destructor

  std::cout << "\n=== Leaving scope ===\n";
  return 0;
  // Destructors called for x4, x3, x2, x1 (in reverse order)
  // Destructor called for vector elements
}

/*
 * $ g++ -o main chapter-13/exercise-13.cc && ./main
 * === Direct initialization ===
 * X() @0x7ff7b424fc5b
 *
 * === Copy initialization ===
 * X(const X&) @0x7ff7b424fc4b
 *
 * === Assignment ===
 * X() @0x7ff7b424fc4a
 * X& operator=(const X&) @0x7ff7b424fc4a
 *
 * === Function arguments ===
 * X(const X&) @0x7ff7b424fc49
 * ~X() @0x7ff7b424fc49
 *
 * === Return values ===
 * X() @0x7ff7b424fc48
 *
 * === Container operations ===
 * X(const X&) @0x6000012ac050
 *
 * === Dynamic allocation ===
 * X(const X&) @0x6000012ac060
 * ~X() @0x6000012ac060
 *
 * === Leaving scope ===
 * ~X() @0x6000012ac050
 * ~X() @0x7ff7b424fc48
 * ~X() @0x7ff7b424fc4a
 * ~X() @0x7ff7b424fc4b
 * ~X() @0x7ff7b424fc5b
 */
