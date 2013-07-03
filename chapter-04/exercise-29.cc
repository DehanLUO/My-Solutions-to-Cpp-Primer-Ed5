/*
 * Exercise 4.29: Predict the output of the following code and explain your
 * reasoning. Now run the program. Is the output what you expected? If not,
 * figure out why.
 * int x[10]; int *p = x;
 * cout << sizeof(x)/sizeof(*x) << endl;
 * cout << sizeof(p)/sizeof(*p) << endl;
 */

#include <iostream>  // std::cout

int main() {
  int x[10];   // Array of 10 integers
  int *p = x;  // Pointer to first element of x

  /*
   * sizeof(x): Size of the entire array (10 * sizeof(int))
   * sizeof(*x): Size of first element (sizeof(int))
   * Calculation: (10 * sizeof(int)) / sizeof(int) = 10
   */
  std::cout << "sizeof(x)/sizeof(*x): " << sizeof(x) / sizeof(*x) << "\n";

  /*
   * sizeof(p): Size of pointer (architecture dependent)
   * sizeof(*p): Size of int
   * Calculation: sizeof(pointer)/sizeof(int)
   */
  std::cout << "sizeof(p)/sizeof(*p): " << sizeof(p) / sizeof(*p) << "\n";

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-29.cc && ./main
 * chapter-04/exercise-29.cc:28:54: warning: 'sizeof (p)' will return the size of the pointer, not the array itself [-Wsizeof-pointer-div]
 *    28 |   std::cout << "sizeof(p)/sizeof(*p): " << sizeof(p) / sizeof(*p) << "\n";
 *       |                                            ~~~~~~~~~ ^
 * chapter-04/exercise-29.cc:14:8: note: pointer 'p' declared here
 *    14 |   int *p = x;  // Pointer to first element of x
 *       |        ^
 * 1 warning generated.
 * sizeof(x)/sizeof(*x): 10
 * sizeof(p)/sizeof(*p): 2
 */
