/*
 * Exercise 7.51: Why do you think vector defines its single-argument
 * constructor as explicit, but string does not?
 */

#include <string>       // std::string
#include <type_traits>  // std::is_convertible
#include <vector>       // std::vector

void ProcessString(const std::string& str) {}

int main() {
  /*
   * string(const char*) is non-explicit because:
   * 1. Natural conversion:
   *    - C-string to string is semantically transparent
   *    - Matches user expectations from C heritage
   *
   * 2. Practical utility:
   *    - Enables seamless interoperability
   *    - Reduces syntactic overhead
   *
   * 3. Historical context:
   *    - Designed for C compatibility
   *    - Widely used in legacy code
   */
  std::string s = "text";  // Intuitive and safe
  ProcessString("hello");  // Expected behavior

  /*
   * vector<size_t> is explicit because:
   * 1. Semantic significance:
   *    - vector<int> v(10) vs vector<int> v = 10
   *    - Former clearly indicates size initialization
   *    - Latter would be misleading (not intuitive)
   *
   * 2. Safety considerations:
   *    - Prevents accidental scalar→vector conversions
   *    - Avoids ambiguous function overloads
   *
   * 3. Design philosophy:
   *    - Size initialization is operationally significant
   *    - Not a "natural" conversion like string's
   */
  // std::vector<int> v = 10;  // Prevented (would be dangerous)
  std::vector<int> v(10);  // Clear size initialization

  return 0;
}

// Static assertions verifying designs
static_assert(std::is_convertible<const char*, std::string>::value,
              "Verifies string's implicit conversion");
static_assert(!std::is_convertible<int, std::vector<int>>::value,
              "Verifies vector's explicit construction");
