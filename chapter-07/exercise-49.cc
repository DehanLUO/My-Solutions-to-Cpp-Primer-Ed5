/*
 * Exercise 7.49: For each of the three following declarations of combine,
 * explain what happens if we call i.combine(s), where i is a Sales_data and s
 * is a string:
 *     (a) Sales_data &combine(Sales_data);
 *     (b) Sales_data &combine(Sales_data&);
 *     (c) Sales_data &combine(const Sales_data&) const;
 */

int main() {
  // Sales_data i;
  // std::string s("9-999-99999-9");

  /* Case (a): Sales_data &combine(Sales_data); */
  /*
   * Behavior:
   * 1. Attempts implicit conversion: string → Sales_data
   * 2. If successful:
   *    - Creates temporary Sales_data object
   *    - Passes by value
   * 3. Requires non-explicit Sales_data(const string&) constructor
   */

  /* Case (b): Sales_data &combine(Sales_data&); */
  /*
   * Behavior:
   * 1. Attempts bind non-const reference to temporary
   * 2. Fails compilation:
   *    - Cannot bind non-const lvalue reference to rvalue
   *    - No implicit conversion occurs
   */

  /* Case (c): Sales_data &combine(const Sales_data&) const; */
  /*
   * Behavior:
   * 1. Compilation error:
   *    - const member function cannot modify *this
   *    - Return type (Sales_data&) conflicts with const
   * 2. Even if return type fixed:
   *    - const member function can't modify object state
   *    - Violates combine()'s intended semantics
   */
  return 0;
}
