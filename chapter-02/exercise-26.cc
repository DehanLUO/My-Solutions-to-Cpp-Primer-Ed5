/*
 * Exercise 2.26: Which of the following are legal? For those that are illegal,
 * explain why.
 *     (a) const int buf;                 (b) int cnt = 0;
 *     (c) const int sz = cnt;            (d) ++cnt; ++sz;
 */

int main() {
  /*
   * Illegal. A const object must be initialized (since it cannot be assigned
   * later.)
   */
  // const int buf;

  /*
   * Legal. The rvalue `0` is used to initialized the lvalue `cnt`.
   */
  int cnt = 0;

  /*
   * Legal. `cnt` is an rvalue. its value is read (lvalue-to-rvalue conversion)
   * to initialize lvalue `sz`.
   */
  const int sz = cnt;

  /*
   * Legal. `cnt` is an lvalue, so it can be modified.
   */
  ++cnt;

  /*
   * Illegal. `sz` is a const lvalue (named, but read-only). Modifying a const
   * object is illegal. The operation voilates `const`-correctness.
   */
  // ++sz;

  return 0;
}
