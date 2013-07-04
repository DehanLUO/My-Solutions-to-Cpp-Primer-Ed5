/*
 * Exercise 7.55: Is the Data class from § 7.5.5 (p. 298) a literal class? If
 * not, why not? If so, explain why it is literal.
 */

#include <string>  // std::string

/**
 * @brief Data class from §7.5.5 examination
 * The Data class is NOT a literal type because:
 *
 * 1. Contains std::string member
 *    - std::string is not a literal type
 *    - Has non-trivial destructor
 *    - Requires runtime initialization
 *
 * 2. Fails aggregate initialization
 *    - Cannot be fully initialized at compile-time
 *    - std::string construction has side effects
 *
 * 3. Violates requirements:
 *    - All members must be literal types
 *    - Must have trivial destructor
 */
struct Data {
  int ival;       // Literal type
  std::string s;  // Non-literal type
};

/**
 * @brief Corrected literal class example
 */
struct LiteralData {
  int ival;       // Literal type
  const char* s;  // Literal type (C-string)

  // Valid constexpr usage:
  constexpr LiteralData(int i, const char* str) : ival(i), s(str) {}
};

int main() {
  // constexpr Data a;

  constexpr LiteralData b(42, "valid");

  return 0;
}
