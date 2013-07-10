/*
 * Exercise 14.47: Explain the difference between these two conversion
 * operators:
 *     struct Integral {
 *       operator const int();
 *       operator int() const;
 *     };
 */

/*
 * KEY DIFFERENCES SUMMARY:
 *
 * operator const int();
 * - Returns a const-qualified int
 * - Method is NOT const-qualified (can modify member variables)
 * - Cannot be called on const objects
 * - Generally not useful for primitive types
 *
 * operator int() const;
 * - Returns a non-const int
 * - Method IS const-qualified (cannot modify member variables)
 * - Can be called on const objects
 * - Standard and recommended approach
 */
