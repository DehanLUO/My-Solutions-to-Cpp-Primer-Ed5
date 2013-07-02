/*
 * Exercise 3.30: Identify the indexing errors in the following code:
 *     constexpr size_t array_size = 10;
 *     int ia[array_size];
 *     for (size_t ix = 1; ix <= array_size; ++ix)
 *       ia[ix] = ix;
 */

#include <vector>  // std::vector

int main() {
  constexpr size_t array_size = 10;
  int ia[array_size];
  /*
   * Off-by-One Error: The loop runs from `ix = 1` to `ix = 10`(`<=
   * array_size)`, but valid indices for `ia[10]` are 0 to 9. `ia[10] =10;`
   * writes out of bounds.
   */
  // for (size_t ix = 1; ix <= array_size; ++ix)
  for (size_t ix = 0; ix < array_size; ++ix)  // Fixed version
    ia[ix] = ix;

  return 0;
}
