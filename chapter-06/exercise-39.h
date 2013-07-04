/*
 * Exercise 6.39: Explain the effect of the second declaration in each one of
 * the following sets of declarations. Indicate which, if any, are illegal.
 *     (a) int calc(int, int);
 *         int calc(const int, const int);
 *     (b) int get();
 *         double get();
 *     (c) int *reset(int *);
 *         double *reset(double *);
 */

// Case (a) - Illegal (const on value parameters doesn't differentiate)
int Calc(int, int);
// int Calc(const int, const int);  // Error: redefinition
/*
 * These declarations are equivalent because:
 * - const on value parameters is irrelevant to the caller
 * - The function signature is identical at call site
 */

// Case (b) - Illegal (return type alone doesn't differentiate)
int Get();
// double Get();  // Error: new declaration conflicts
/*
 * These cannot coexist because:
 * - Overloading requires parameter type differences
 * - The compiler can't determine which version to call
 */

// Case (c) - Legal (different parameter types)
int* Reset(int*);
double* Reset(double*);  // Valid overload
/*
 * These are valid because:
 * - The parameter types are fundamentally different
 * - The compiler can distinguish calls based on argument types
 */
