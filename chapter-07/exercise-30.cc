/*
 * Exercise 7.30: It is legal but redundant to refer to members through the this
 * pointer. Discuss the pros and cons of explicitly using the this pointer to
 * access members.
 */

#include <string>  // std::string

class Example {
 private:
  std::string name;
  int value;

 public:
  // ===== PROS OF EXPLICIT 'this->' =====

  /**
   * @brief Constructor demonstrating disambiguation
   * @param name Parameter shadowing member name
   * @param value Parameter shadowing member value
   *
   * Using 'this->' resolves naming conflicts between
   * parameters and member variables.
   */
  Example(const std::string& name, int value) {
    this->name = name;    // Clear which 'name' is meant
    this->value = value;  // Removes ambiguity
  }

  /**
   * @brief Shows explicit member access in templates
   *
   * In template code, 'this->' may be required when:
   * - Base class members aren't visible
   * - Dependent name lookup is needed
   */
  template <typename T>
  void TemplateMethod(T param) {
    this->value = param;  // Often necessary in templates
  }

  // ===== CONS OF EXPLICIT 'this->' =====

  /**
   * @brief Normal method showing verbosity
   *
   * Excessive 'this->' can:
   * - Make code visually noisy
   * - Add unnecessary typing
   * - Obscure simple member access
   */
  void NormalMethod() {
    this->name = "Default";  // 'this->' adds little value here
    this->value = 0;         // When no ambiguity exists
  }

  // ===== RECOMMENDED PRACTICES =====

  /**
   * @brief Balanced approach example
   *
   * Best practices suggest:
   * - Use 'this->' only when necessary
   * - Prefer unique naming to avoid shadowing
   * - Require it in template contexts
   */
  void RecommendedMethod(int new_value) {
    name = "Recommended";  // Clean without 'this->'
    value = new_value;     // When no ambiguity

    // Use when helpful for readability
    if (this->value < 0) {  // Makes 'value' stand out
      this->value = 0;
    }
  }
};

/*
 * Professional Guidelines:
 *
 * 1. Required Uses:
 *    - Parameter/member name conflicts
 *    - Template base class members
 *    - Returning *this for chaining
 *
 * 2. Optional Uses:
 *    - Emphasizing member access
 *    - Consistency in codebase
 *    - Visual distinction from locals
 *
 * 3. Avoid When:
 *    - No naming ambiguity exists
 *    - It reduces code clarity
 *    - Just following "style" without purpose
 *
 * 4. Team Considerations:
 *    - Follow project conventions
 *    - Be consistent within a codebase
 *    - Document style decisions
 */

int main() {
  Example ex("Test", 42);
  ex.RecommendedMethod(10);
  return 0;
}
