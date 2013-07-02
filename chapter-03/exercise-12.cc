/*
 * Exercise 3.12: Which, if any, of the following vector definitions are in
 * error? For those that are legal, explain what the definition does. For those
 * that are not legal, explain why they are illegal.
 *     (a) vector<vector<int>> ivec;
 *     (b) vector<string> svec = ivec;
 *     (c) vector<string> svec(10, "null");
 */

#include <string>  // std::string
#include <vector>  // std::vector

int main() {
  using std::string;
  using std::vector;

  vector<vector<int>> ivec;  //  Legal. Creates an empty vector of `vector<int>`

  /*
   * Illegal. Type mismatch. Cannot initialize `vector<string>` with
   * `vector<vector<int>>`.
   */
  // vector<string> svec = ivec;

  /*
   * Legal. Constructor form: `vector(size_type count, const T& value)`. Creates
   * a vector of 10 strings, each initialized to "null"
   *
   */
  vector<string> svec(10, "null");

  return 0;
}
