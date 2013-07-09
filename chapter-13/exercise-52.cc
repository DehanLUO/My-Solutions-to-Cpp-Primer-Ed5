/*
 * Exercise 13.52: Explain in detail what happens in the assignments of the
 * HasPtr objects on page 541. In particular, describe step by step what happens
 * to values of hp, hp2, and of the rhs parameter in the HasPtr assignment
 * operator.
 */

#include "exercise-52.h"  // HasPtr

int main() {
  HasPtr hp, hp2;

  /*
   * Step 1: Parameter initialization:
   *    - hp2 is an lvalue → copy constructor creates rhs parameter
   *    - HasPtr(const HasPtr& other) executes:
   *      * Allocates new string (*other.ps)
   *      * Copies integer value
   *    - Now we have:
   *      * hp (original data)
   *      * hp2 (original data)
   *      * rhs (copy of hp2)
   *
   * 2. Assignment operator body:
   *    - swap(*this, rhs) executes:
   *      * Exchanges ps and i between hp and rhs
   *      * Now:
   *        - hp contains copy of hp2's data
   *        - rhs contains hp's original data
   *
   * 3. Parameter cleanup:
   *    - rhs (now holding hp's original data) is destroyed
   *    - Destructor deletes the original string hp was managing
   *
   * Final state:
   * - hp contains a copy of hp2's data
   * - hp2 remains unchanged
   */
  hp = hp2;  // hp2 is an lvalue; copy constructor used to copy hp2

  /*
   * Step 1: Parameter construction
   * - std::move makes hp2 rvalue → HasPtr(HasPtr&&) called
   * - Creates temporary rhs with:
   *   * Direct pointer transfer (no allocation)
   *   * hp2.ps set to nullptr
   *
   * Step 2: swap execution
   * - Exchanges:
   *   * ps pointers (now moving hp2's string to hp)
   *   * i values
   *
   * Step 3: Parameter destruction
   * - rhs (now holding old hp data) is destroyed
   * - Deletes the old string hp was managing
   * - hp2 left in valid but empty state (ps = nullptr)
   */
  hp = std::move(hp2);  // move constructor moves hp2
}

/*
 * $ g++ -o main chapter-13/exercise-52.cc && ./main
 * HasPtr(const std::string& s = std::string())
 * HasPtr(const std::string& s = std::string())
 * HasPtr(const HasPtr& other):
 * HasPtr& operator=(HasPtr rhs)
 * ==> Executing swap between "" and ""
 * HasPtr(HasPtr&& other) noexcept:
 * HasPtr& operator=(HasPtr rhs)
 * ==> Executing swap between "" and ""
 */
