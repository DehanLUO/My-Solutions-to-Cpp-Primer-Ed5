/*
 * Exercise 13.46: Which kind of reference can be bound to the following
 * initializers?
 *     int f();
 *     vector<int> vi(100);
 *     int? r1 = f();
 *     int? r2 = vi[0];
 *     int? r3 = r1;
 *     int? r4 = vi[0] * f();
 */

#include <vector>  // std::vector

int f() { return 0; }  // Function returning by value (creates temporary)

int main() {
  std::vector<int> vi(100);  // vector with 100 elements

  // Case 1: Function returning by value (rvalue)
  int&& r1 = f();  // f() returns temporary (rvalue) - needs rvalue reference

  // Case 2: Vector element access (lvalue)
  int& r2 = vi[0];  // vi[0] returns reference to existing element (lvalue)

  // Case 3 : Reference to another reference(lvalue)
  int& r3 = r1;  // r1 is a named reference (lvalue) - needs lvalue reference

  // Case 4: Arithmetic operation result (rvalue)
  // Multiplication yields temporary (rvalue) - needs rvalue reference
  int&& r4 = vi[0] * f();

  return 0;
}
