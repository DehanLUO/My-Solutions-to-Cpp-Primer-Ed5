/*
 * Exercise 8.9: Use the function you wrote for the first exercise in § 8.1.2
 * (p. 314) to print the contents of an istringstream object.
 */

#include <sstream>  // std::istringstream

#include "exercise-01.h"  // ProcessInputStream

int main() {
  constexpr char test[] = "The quick brown fox jumps over the lazy dog.";
  std::istringstream iss(test);

  ProcessInputStream<std::string>(iss);

  return 0;
}

/*
 * $ g++ -o main chapter08/exercise-09.cc && ./main
 * The quick brown fox jumps over the lazy dog.
 */
