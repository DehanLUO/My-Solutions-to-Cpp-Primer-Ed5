/*
 * Exercise 6.5: Write a function to return the absolute value of its argument.
 */

/**
 * @brief Returns the absolute value of a number
 * @tparam T Numeric type (int, double, etc.)
 * @param val Input value
 * @return Absolute value of the input
 *
 * Features:
 * - Works with all standard numeric types
 * - Compile-time type checking
 * - Simple and efficient implementation
 */
template <typename T>
T AbsoluteValue(T val) {
  return val < 0 ? -val : val;
}

int main() {
  // Example usage
  int x = -5;
  double y = -3.14;

  // The function works with different numeric types
  int abs_x = AbsoluteValue(x);     // abs_x will be 5
  double abs_y = AbsoluteValue(y);  // abs_y will be 3.14

  return 0;
}
