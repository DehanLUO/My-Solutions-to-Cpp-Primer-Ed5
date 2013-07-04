/*
 * Exercise 6.31: When is it valid to return a reference? A reference to const?
 */

#include <string>  // std::string

// Example class for demonstration
class MyContainer {
  std::string data;

 public:
  // Valid case 1: Returning reference to member variable
  std::string& GetData() { return data; }  // Mutable reference

  // Valid case 2: Returning const reference to member
  const std::string& GetDataConst() const { return data; }  // Const reference

  // Dangerous case: Returning reference to local variable
  std::string& BadReference() {
    std::string local = "danger";
    return local;  // Undefined behavior - local will be destroyed
  }
};

// Valid case 3: Returning reference to static variable
std::string& GetGlobalString() {
  static std::string s = "safe";
  return s;  // Safe because static persists
}

// Valid case 4: Returning reference to const static
const std::string& GetGlobalStringConst() {
  static const std::string s = "safe";
  return s;  // Safe const reference
}

/*
 * When to return references:
 *
 * 1. Valid to return reference when:
 *    - Returning reference to existing object that will outlive the function
 * call
 *    - Common cases:
 *      a) Returning reference to class member (getter)
 *      b) Returning reference to static/global variable
 *      c) Returning reference to parameter that will persist
 *
 * 2. Valid to return const reference when:
 *    - You want to allow read-only access
 *    - All the above cases where modification shouldn't be allowed
 *    - Particularly important for operator[] in const contexts
 *
 * 3. Never return reference when:
 *    - Reference would be to a local variable
 *    - Reference would be to a temporary
 *    - Reference would outlive the referred object
 */

int main() {
  MyContainer obj;

  // Valid uses
  std::string& d1 = obj.GetData();             // Can modify
  const std::string& d2 = obj.GetDataConst();  // Read-only

  std::string& gs = GetGlobalString();              // Safe
  const std::string& gsc = GetGlobalStringConst();  // Safe

  // Dangerous case (undefined behavior)
  // std::string& bad = obj.badReference();

  return 0;
}
