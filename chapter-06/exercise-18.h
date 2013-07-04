/*
 * Exercise 6.18: Write declarations for each of the following functions. When
 * you write these declarations, use the name of the function to indicate what
 * the function does.
 *     (a) A function named compare that returns a bool and has
 *         two parameters that are references to a class named matrix.
 *     (b) A function named change_val that returns a vector<int> iterator and
 *         takes two parameters: One is an int and the other is an iterator for
 *         a vector<int>.
 */

#include <vector>  // std::vector

// Forward declaration of matrix class
class matrix;

/**
 * (a) Compares two matrix objects
 * @param m1 First matrix to compare
 * @param m2 Second matrix to compare
 * @return bool True if matrices are equal
 */
bool Compare(const matrix& m1, const matrix& m2);

/**
 * (b) Changes a value in a vector and returns iterator to next element
 * @param val New integer value to insert
 * @param it Iterator pointing to position to change
 * @return vector<int>::iterator Iterator to next element after changed value
 */
std::vector<int>::iterator ChangeVal(int val, std::vector<int>::iterator it);

/*
 * Declaration Notes:
 *
 * For (a) compare function:
 * 1. Uses const references since comparison shouldn't modify matrices
 * 2. Name clearly indicates it performs comparison
 * 3. Return type bool is appropriate for comparison
 *
 * For (b) change_val function:
 * 1. Takes int by value (small, primitive type)
 * 2. Takes iterator by value (iterators are typically passed by value)
 * 3. Returns iterator to enable chaining operations
 * 4. Name indicates it changes a value in the container
 */
