/*
 * Exercise 3.28: What are the values in the following arrays?
 *     string sa[10];
 *     int ia[10];
 *     int main() {
 *       string sa2[10];
 *       int ia2[10];
 *     }
 */

#include <string>  // std::string

#include "../include/type_util.h"

// Data segment. Initialized with default construct. 10 empty strings.
std::string sa[10];
// Data segment. Zero-initialized. 10 zeros.
int ia[10];
int main() {
  PRINT_VAR_TYPE(sa);
  PRINT_VAR_TYPE(ia);

  // Stack. Initialized with default construct. 10 empty strings.
  std::string sa2[10];
  PRINT_VAR_TYPE(sa2);

  // Stack. Uninitialized. 10 garbage values.
  int ia2[10];
  PRINT_VAR_TYPE(ia2);

  return 0;
}

/*
 * $ g++ -o main chapter-03/exercise-28.cc && ./main
 * sa: [, , , , , , , , , ] |type: std::string[10]
 * ia: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0] |type: int[10]
 * sa2: [, , , , , , , , , ] |type: std::string[10]
 * ia2: [-1330361504, 32759, 330733280, 1, 10, 0, 124053342, 32760, 344064, 0] |type: int[10] |type: int[10]
 */