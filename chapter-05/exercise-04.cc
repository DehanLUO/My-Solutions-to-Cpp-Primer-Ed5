// Exercise 5.4: Explain each of the following examples, and correct any
// problems you detect.
//     (a) while (string::iterator iter != s.end()) { /* . . . */ }
//     (b) while (bool status = find(word)) { /* . . . */ }
//       if (!status) { /* . . . */}

#include <string>  // std::string

int main() {
  std::string s = "example";
  std::string word = "word";

  // Problem (a) Analysis:
  // - Declares iterator inside while condition but doesn't initialize it
  // - Scope issue: 'iter' only exists in the while condition

  // Corrected version (a):
  std::string::iterator iter = s.begin();
  while (iter != s.end()) {
    // Use the iterator...
    ++iter;
  }

  // Problem (b) Analysis:
  // - 'status' is declared in while condition, so it's out of scope for the if
  // - The if statement can't see the status variable

  // Corrected version (b):
  bool status;
  while (status = s.find(word)) {
    // Do something...

    /*
     * std::string::find returns a value of type std::size_t. If the word is not
     * found, it returns std::string::npos, which is a very large positive
     * number, not 0.
     * Because `status = s.find(word)` is an assignment, its result is
     * interpreted as a truthy value in the while condition --- as long as it is
     * not non-zero. So even if the word is not found, the loop may still run
     * code, because std::string::npos is not 0.
     *
     * Since the word is not found at index 0, the result is never 0, which is
     * treated as false, so we need a break to skip the loop.
     */
    break;
  }
  if (!status) {
    // Handle not found case
  }

  // Alternative better version (b):
  while (bool current_status = s.find(word)) {
    // Do something...
    // status only available in loop
    // If needed outside, must use first correction
    break;
  }

  return 0;
}
