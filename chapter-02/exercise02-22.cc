/*
 * Exercise 2.22: Assuming p is a pointer to int, explain the following code:
 *     if (p) // ...
 *     if (*p) // ...
 */

int main() {
  int variable;

  int* p = &variable;

  /*
   * Checks whether the pointer `p` is non-null(i.e., not nullptr or NULL).
   * Since `p` is assigned `&variable`, it holds a valid address,
   * evaluates to true.
   */
  if (p)
    ;

  /*
   * Dereference p and checks the value of variable. `variable` is an
   * uninitialized stack variable, meaning its value is indeterminate. Reading
   * an uninitialized variable is Undefined Behavior in c++.
   */
  if (*p)
    ;

  return 0;
}
