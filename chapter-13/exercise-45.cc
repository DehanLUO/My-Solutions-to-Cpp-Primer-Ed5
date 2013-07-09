/*
 * Exercise 13.45: Distinguish between an rvalue reference and an lvalue
 * reference.
 */

/*
 * Key Differences:
 * 1. Syntax:
 *    - Lvalue reference:  T& (binds to lvalues)
 *    - Rvalue reference: T&& (binds to rvalues)
 * 2. Binding Behavior:
 *    - Lvalue references:
 *      * Can bind to variables with names (lvalues)
 *      * Can bind to modifiable persistent objects
 *      * Example:
 *        int x = 5;
 *        int& lref = x;  // Valid
 *    - Rvalue references:
 *      * Can bind to temporaries (rvalues)
 *      * Can bind to objects about to be destroyed
 *      * Enable move semantics
 *      * Example:
 *        int&& rref = 5;            // Valid
 *        int&& rref2 = x + 1;       // Valid (temporary)
 *        int&& rref3 = std::move(x); // Valid (explicit rvalue)
 * 3. Lifetime Implications:
 *    - Lvalue references extend the lifetime of temporaries when const
 *      const int& clref = 5;  // Lifetime extended
 *    - Rvalue references don't require const to bind to temporaries
 * 4. Primary Use Cases:
 *    - Lvalue references:
 *      * Traditional reference parameters
 *      * Aliasing existing variables
 *      * Avoiding copies in function calls
 *    - Rvalue references:
 *      * Move constructors/assignment
 *      * Perfect forwarding
 *      * Temporary object handling
 * 5. Overload Resolution:
 *    - Functions can be overloaded based on reference type:
 *      void process(int&);   // Lvalue version
 *      void process(int&&);  // Rvalue version
 * 6. Key Properties:
 *    - Lvalue references:
 *      * Identity (has a name/address)
 *      * Persistence beyond single expression
 *    - Rvalue references:
 *      * Anonymous temporaries
 *      * Can be safely "moved from"
 *      * Typically don't persist beyond expression
 */

#include <utility>  // for std::move

void demonstrate_references() {}

int main() {
  int x = 10;  // x is an lvalue

  // Lvalue reference examples
  int& lref1 = x;  // Valid - binding to lvalue
  // int& lref2 = 5;  // Invalid - can't bind to rvalue

  // Rvalue reference examples
  int&& rref1 = 5;             // Valid - binding to rvalue
  int&& rref2 = x + 3;         // Valid - binding to temporary
  int&& rref3 = std::move(x);  // Valid - explicit rvalue

  // Const lvalue reference special case
  const int& clref = 5;  // Valid - lifetime extension

  return 0;
}
