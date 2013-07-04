/*
 * Exercise 6.40: Which, if either, of the following declarations are errors?
 * Why?
 *     (a) int ff(int a, int b = 0, int c = 0);
 *     (b) char *init(int ht = 24, int wd, char bckgrnd);
 */

// Valid declaration (all defaults at end)
int ValidFunction(int a, int b = 0, int c = 0);

// Invalid declaration (non-default follows default)
// char* InvalidFunction(int ht = 24, int wd, char bckgrnd);
/*
 * This violates default argument rules because:
 * - 'wd' is non-default but follows default 'ht'
 * - 'bckgrnd' has no default while preceding parameters do
 */
