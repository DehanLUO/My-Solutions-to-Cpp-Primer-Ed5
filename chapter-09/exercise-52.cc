/*
 * Exercise 9.52: Use a stack to process parenthesized expressions. When you see
 * an open parenthesis, note that it was seen. When you see a close parenthesis
 * after an open parenthesis, pop elements down to and including the open
 * parenthesis off the stack. push a value onto the stack to indicate that a
 * parenthesized expression was replaced.
 */

#include <cctype>    // size_t
#include <iostream>  // std::cout
#include <stack>     // std::stack
#include <string>    // std::string

/**
 * @brief Processes a string with parenthesized expressions using a stack
 * @param input The input string to process
 * @return The processed string with parenthesized expressions replaced
 */
std::string ProcessParentheses(const std::string& input) {
  std::stack<size_t> paren_stack;  // Stores positions of open parentheses
  std::string result;

  for (size_t i = 0; i < input.size(); ++i) {
    char c = input[i];

    if (c == '(') {
      // Push the position of the open parenthesis
      paren_stack.push(result.size());
    } else if (c == ')') {
      if (!paren_stack.empty()) {
        // Get the position of the matching open parenthesis
        size_t open_pos = paren_stack.top();
        paren_stack.pop();

        // Replace the parenthesized expression with a placeholder
        result.erase(open_pos, result.size() - open_pos);
        result += "#";  // Placeholder for processed expression
      } else {
        // Unmatched close parenthesis - keep in result
        result += c;
      }
    } else {
      // Regular character - add to result
      result += c;
    }
  }

  // Handle any unmatched open parentheses
  while (!paren_stack.empty()) {
    size_t open_pos = paren_stack.top();
    paren_stack.pop();
    result.insert(open_pos, "(");  // Restore unmatched open parenthesis
  }

  return result;
}

int main() {
  std::vector<std::string> test_cases = {
      "a + (b + c)",          // Simple nested
      "((a + b) * c)",        // Multiple nested
      "a + b)",               // Unmatched close
      "(a + (b * c)",         // Unmatched open
      "no parentheses here",  // No parentheses
      "(a + (b / (c - d)))"   // Deeply nested
  };

  for (const auto& test : test_cases) {
    std::cout << "Original: " << test << '\n';
    std::cout << "Processed: " << ProcessParentheses(test) << '\n';
    std::cout << "---" << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-52.cc && ./main
 * Original: a + (b + c)
 * Processed: a + #
 * ---
 * Original: ((a + b) * c)
 * Processed: #
 * ---
 * Original: a + b)
 * Processed: a + b)
 * ---
 * Original: (a + (b * c)
 * Processed: (a + #
 * ---
 * Original: no parentheses here
 * Processed: no parentheses here
 * ---
 * Original: (a + (b / (c - d)))
 * Processed: #
 * ---
 */
