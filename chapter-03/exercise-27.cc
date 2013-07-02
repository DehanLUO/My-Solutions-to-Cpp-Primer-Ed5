/*
 * Exercise 3.27: Assuming txt_size is a function that takes no arguments and
 * returns an int value, which of the following definitions are illegal? Explain
 * why.
 *     unsigned buf_size = 1024;
 *     (a) int ia[buf_size];
 *     (b) int ia[4 * 7 - 14];
 *     (c) int ia[txt_size()];
 *     (d) char st[11] = "fundamental";
 */

int main() {
  unsigned buf_size = 1024;

  // Illegal. Array size must be a const expression.
  // `buf_size` is a non-const variable.
  // int ia[buf_size];

  // Legal. The size is a const expression (14) known at compile time.
  int ib[4 * 7 - 14];

  // Illegal. Function calls `txt_szie()` are not constant expressions.
  // int ic[txt_size()];

  // Illegal. The string literal requires 12 bytes (11 chars + null terminator).
  // But the array only has 11.
  // char st[11] = "fundamental";

  return 0;
}
