/*
 * Exercise 6.38: Revise the arrPtr function on to return a reference to the
 * array.
 *     int odd[] = {1, 3, 5, 7, 9};
 *     int even[] = {0, 2, 4, 6, 8};
 *     // returns a pointer to an array of five int elements
 *     decltype(odd) *arrPtr(int i){
 *       return (i % 2) ? &odd : &even; // returns a pointer to the array
 *     }
 */

#include <iostream>  // std::cout

// Global arrays as given in the exercise
int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};

/**
 * @brief Returns a reference to an array of five integers
 * @param i Integer determining which array to return
 * @return int (&)[5] Reference to the selected array
 *
 * Revised version that returns a reference instead of pointer:
 * 1. More intuitive syntax for array access
 * 2. Avoids pointer arithmetic pitfalls
 * 3. Maintains array size information
 */
auto ArrRef(int i) -> int (&)[5] {
  /*
   * Selection logic remains the same but now returns:
   * - A reference to the entire array
   * - Type includes array dimension for safety
   */
  return (i % 2) ? odd : even;
}

/**
 * @brief Demonstrates usage of array reference return
 */
void DemonstrateArrayReference() {
  /*
   * Key advantages of reference return:
   * 1. Direct access to array elements without dereferencing
   * 2. Preserved array size information
   * 3. More natural syntax matching array semantics
   */
  auto& arr1 = ArrRef(1);  // Gets reference to odd array
  auto& arr2 = ArrRef(2);  // Gets reference to even array

  // Size information preserved (compile-time known)
  static_assert(sizeof(arr1) / sizeof(arr1[0]) == 5, "Array size preserved");

  // Can use range-based for loops directly
  for (int num : ArrRef(1)) {
    std::cout << num << " ";  // Prints odd array elements
  }
}

/*
 * Technical Comparison:
 *
 * Original pointer version:
 * - Required dereferencing: (*arrPtr(1))[0]
 * - Lost array size information
 * - Pointer arithmetic possible
 *
 * Reference version:
 * - Direct element access: ArrRef(1)[0]
 * - Maintains array type with size
 * - Prevents pointer arithmetic
 * - More idiomatic C++ usage
 */

int main() {
  DemonstrateArrayReference();
  return 0;
}

/* $ g++ -o main chapter-06/exercise-38.cc && ./main
 * 1 3 5 7 9
 */
