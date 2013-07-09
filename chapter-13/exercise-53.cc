/*
 * Exercise 13.53: As a matter of low-level efficiency, the HasPtr assignment
 * operator is not ideal. Explain why. Implement a copy-assignment and
 * move-assignment operator for HasPtr and compare the operations executed in
 * your new move-assignment operator versus the copy-and-swap version.
 */

#include "exercise-53.h"  // HasPtr

int main() {
  HasPtr hp, hp2;

  hp = hp2;

  hp = std::move(hp2);
}

/*
 * $ g++ -o main chapter-13/exercise-53.cc && ./main
 * HasPtr(const std::string& s = std::string())
 * HasPtr(const std::string& s = std::string())
 * HasPtr& operator=(const HasPtr& rhs)
 * HasPtr& operator=(HasPtr&& rhs)
 * ==> Executing swap between "" and ""
 */
