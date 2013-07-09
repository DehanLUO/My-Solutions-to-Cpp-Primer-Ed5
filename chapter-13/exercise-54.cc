/*
 * Exercise 13.54: What would happen if we defined a HasPtr move-assignment
 * operator but did not change the copy-and-swap operator? Write code to test
 * your answer.
 */

/*
 * When both copy-and-swap and move assignment exist:
 * 
 * 1. For hp = hp2 (copy assignment):
 *    - Both operators are viable:
 *      a) operator=(const HasPtr&) (exact match)
 *      b) operator=(HasPtr) (requires copy construction)
 *    - Standard says both are equally good matches → ambiguity
 * 
 * 2. For hp = std::move(hp2) (move assignment):
 *    - Three viable operators:
 *      a) operator=(const HasPtr&) (requires lvalue conversion)
 *      b) operator=(HasPtr&&) (exact match)
 *      c) operator=(HasPtr) (requires move construction)
 *    - operator=(HasPtr&&) and operator=(HasPtr) are equally good → ambiguity
 */

#include "exercise-54.h"  // HasPtr

int main() {
  HasPtr hp, hp2;

  hp = hp2;

  hp = std::move(hp2);
}

/*
 * $ g++ -o main chapter-13/exercise-54.cc
 * chapter-13/exercise-54.cc:12:6: error: use of overloaded operator '=' is ambiguous (with operand types 'HasPtr' and 'HasPtr')
 *    12 |   hp = hp2;
 *       |   ~~ ^ ~~~
 * chapter-13/exercise-54.h:55:11: note: candidate function
 *    55 |   HasPtr& operator=(const HasPtr& rhs) {
 *       |           ^
 * chapter-13/exercise-54.h:80:11: note: candidate function
 *    80 |   HasPtr& operator=(HasPtr rhs) {
 *       |           ^
 * chapter-13/exercise-54.cc:14:6: error: use of overloaded operator '=' is ambiguous (with operand types 'HasPtr' and '__libcpp_remove_reference_t<HasPtr &>' (aka 'HasPtr'))
 *    14 |   hp = std::move(hp2);
 *       |   ~~ ^ ~~~~~~~~~~~~~~
 * chapter-13/exercise-54.h:55:11: note: candidate function
 *    55 |   HasPtr& operator=(const HasPtr& rhs) {
 *       |           ^
 * chapter-13/exercise-54.h:74:11: note: candidate function
 *    74 |   HasPtr& operator=(HasPtr&& rhs) {
 *       |           ^
 * chapter-13/exercise-54.h:80:11: note: candidate function
 *    80 |   HasPtr& operator=(HasPtr rhs) {
 *       |           ^
 * 2 errors generated.
 */
