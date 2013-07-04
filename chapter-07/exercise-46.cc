/*
 * Exercise 7.46: Which, if any, of the following statements are untrue? Why?
 *     (a) A class must provide at least one constructor.
 *     (b) A default constructor is a constructor with an empty parameter list.
 *     (c) If there are no meaningful default values for a class, the class
 *         should not provide a default constructor.
 *     (d) If a class does not define a default constructor, the compiler
 *         generates one that initializes each data member to the default value
 *         of its associated type.
 */

int main() {
  /*
   * Statement (a) Analysis:
   * - False: Classes get implicit default constructor if no others declared
   * - Example:
   */
  struct ImplicitDefault {
    int value;
  };
  ImplicitDefault a;  // Legal despite no declared constructors

  /*
   * Statement (b) Analysis:
   * - False: Default constructors can have all-default parameters
   * - Example:
   */
  struct DefaultParams {
    DefaultParams(int x = 0) {}  // Counts as default constructor
  };
  DefaultParams b;  // Legal despite non-empty parameter list

  /*
   * Statement (c) Analysis:
   * - Opinion: Not universally true
   * - Many designs provide default constructors for container compatibility
   * - Example:
   */
  struct NoMeaningfulDefault {
    NoMeaningfulDefault() = delete;  // Explicitly prevent
    NoMeaningfulDefault(int x) {}
  };
  // NoMeaningfulDefault c;  // Would be illegal

  /*
   * Statement (d) Analysis:
   * - False: Only if no user-declared constructors exist
   * - Example:
   */
  struct NoCompilerDefault {
    NoCompilerDefault(int x) {}
    // No default constructor generated
  };
  // NoCompilerDefault d;  // Would be illegal

  return 0;
}
