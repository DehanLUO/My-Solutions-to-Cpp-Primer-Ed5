/*
 * Exercise 14.3: Both string and vector define an overloaded == that can be
 * used to compare objects of those types. Assuming svec1 and svec2 are vectors
 * that hold strings, identify which version of == is applied in each of the
 * following expressions:
 *     (a) "cobble" == "stone"     (b) svec1[0] == svec2[0]
 *     (c) svec1 == svec2          (d) svec1[0] == "stone"
 */

#include <string>  // std::string
#include <vector>  // std::vector

int main() {
  std::vector<std::string> svec1(1), svec2(1);

  /*
   * Type: const char[7] == const char[6]
   * Resolution:
   * - Built-in operator== for C-style strings (const char*)
   * - Compares pointer values (addresses), not string contents
   * - This is usually not the intended behavior!
   *
   * Better practice:
   * - Use std::string comparison: std::string("cobble") == "stone"
   * - Or use strcmp() for C-style strings
   */
  "cobble" == "stone";

  /*
   * Type: std::string == std::string
   * Resolution:
   * - Calls std::string::operator==
   * - Compares string contents lexicographically
   * - Exact overload: bool operator==(const string&, const string&)
   *
   * Implementation:
   * - Compares character sequences
   * - Returns true only if identical content
   */
  svec1[0] == svec2[0];

  /*
   * Type: vector<string> == vector<string>
   * Resolution:
   * - Calls std::vector::operator==
   * - Exact overload: bool operator==(const vector<T>&, const vector<T>&)
   *
   * Comparison rules:
   * 1. First compares sizes
   * 2. Then compares each element using T's operator==
   *    (in this case, std::string::operator==)
   *
   * Note:
   * - Requires element type (std::string) to have == defined
   */
  svec1 == svec2;

  /*
   * Type: std::string == const char[6]
   * Resolution:
   * - Calls std::string::operator==
   * - Exact overload: bool operator==(const string&, const char*)
   *
   * Behavior:
   * - Converts const char* to temporary std::string
   * - Compares string contents
   * - More efficient than case (a) as it properly compares contents
   *
   * Note:
   * - Works due to std::string's implicit conversion constructor
   * - But explicit conversion is often clearer:
   *   svec1[0] == std::string("stone")
   */
  svec1[0] == "stone";

  return 0;
}
