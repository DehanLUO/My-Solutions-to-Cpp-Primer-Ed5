/*
 * Exercise 6.15: Explain the rationale for the type of each of find_char’s
 * parameters In particular, why is s a reference to const but occurs is a plain
 * reference? Why are these parameters references, but the char parameter c is
 * not? What would happen if we made s a plain reference? What if we made occurs
 * a reference to const?
 *     std::string::size_tye find_char(const string &s,
 *                                     char c,
 *                                     std::string::size_type &occurs) {
 *       auto ret = s.size();  // position of the first occurrence, if any
 *       occurs = 0;           // set the occurrence count parameter
 *       for (decltype(ret) != 0; i != s.size(); ++i) {
 *         if (s[i] == c)
 *           ret = i;  // remember the first occurence of c
 *         ++occurs;   // increment the occurence count
 *       }
 *     }
 *     return ret;  // count is returned implicitly in occurs
 *   }
 */

#include <iostream>  // std::cout
#include <string>    // std::string

// Original function with corrected syntax
std::string::size_type find_char(const std::string &s, char c,
                                 std::string::size_type &occurs) {
  auto ret = s.size();  // position of the first occurrence, if any
  occurs = 0;           // set the occurrence count parameter
  for (decltype(ret) i = 0; i != s.size(); ++i) {
    if (s[i] == c) {
      if (ret == s.size()) ret = i;  // remember the first occurrence of c
      ++occurs;                      // increment the occurrence count
    }
  }
  return ret;  // count is returned implicitly in occurs
}

/*
 * Parameter Rationale:
 *
 * 1. const std::string &s:
 *    - Reference: Avoid copying potentially large string
 *    - const: Guarantees we won't modify the input string
 *    - If plain reference:
 *      * Couldn't pass string literals or const strings
 *      * Caller would worry about their string being modified
 *
 * 2. char c:
 *    - Pass by value because:
 *      * char is tiny (1 byte)
 *      * No need to modify original
 *      * Copy is cheaper than indirection
 *
 * 3. std::string::size_type &occurs:
 *    - Must be reference to modify caller's variable
 *    - Acts as an output parameter
 *    - If const reference:
 *      * Couldn't update the count
 *      * Would break the function's purpose
 */

int main() {
  std::string test = "Hello world";
  std::string::size_type count = 0;

  // Proper usage
  auto pos = find_char(test, 'l', count);
  std::cout << "First 'l' at: " << pos << ", count: " << count << '\n';

  // Demonstration of constraints:
  const std::string const_str = "const string";
  // find_char(const_str, 'l', count); // Would fail if s wasn't const

  return 0;
}

/* $ g++ -o main chapter-06/exercise-15.cc && ./main
 * First 'l' at: 2, count: 3
 */
