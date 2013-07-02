/*
 * Exercise 4.20: Assuming that iter is a vector<string>::iterator, indicate
 * which, if any, of the following expressions are legal. Explain the behavior
 * of the legal expressions and why those that aren’t legal are in error.
 *     (a) *iter++;
 *     (b) (*iter)++;
 *     (c) *iter.empty();
 *     (d) iter->empty();
 *     (e) ++*iter;
 *     (f) iter++->empty();
 */

#include <iostream>  // std::cout
#include <string>    // std::string
#include <vector>    // std::vector

/**
 * @brief Demonstrates legal and illegal iterator operations
 */
void ExplainIteratorExpressions() {
  std::vector<std::string> words = {"hello", "world", "cpp"};
  auto iter = words.begin();

  // Case (a): *iter++;
  {
    std::cout << "Case (a) *iter++:\n";
    // Legal - equivalent to *(iter++);
    std::cout << "  Legal: Dereferences current iter, then increments\n";
    std::cout << "  Returns: \"" << *iter++ << "\"\n";
    std::cout << "  Now points to: \"" << *iter << "\"\n";
  }

  // Case (b): (*iter)++;
  {
    std::cout << "\nCase (b) (*iter)++:\n";
    // Illegal - attempts to increment string object
    std::cout << "  Illegal: Cannot increment a string\n";
    // (*iter)++ would try to modify the string itself
  }

  // Case (c): *iter.empty();
  {
    std::cout << "\nCase (c) *iter.empty():\n";
    // Illegal - wrong operator precedence
    std::cout << "  Illegal: Parses as *(iter.empty())\n";
    std::cout << "  Iterators don't have empty() method\n";
  }

  // Case (d): iter->empty();
  {
    std::cout << "\nCase (d) iter->empty():\n";
    // Legal - checks if current string is empty
    std::cout << "  Legal: Calls empty() on current string\n";
    std::cout << "  Current string empty? " << (iter->empty() ? "yes" : "no")
              << "\n";
  }

  // Case (e): ++*iter;
  {
    std::cout << "\nCase (e) ++*iter:\n";
    // Illegal - attempts to increment string object
    std::cout << "  Illegal: Cannot increment a string\n";
    // ++*iter would try to modify the string itself
  }

  // Case (f): iter++->empty();
  {
    std::cout << "\nCase (f) iter++->empty():\n";
    // Legal - calls empty() then increments
    std::cout << "  Legal: Calls empty() on current string, then increments\n";
    std::cout << "  Current string empty? " << (iter++->empty() ? "yes" : "no")
              << "\n";
    std::cout << "  Now points to: \"" << *iter << "\"\n";
  }
}

int main() {
  ExplainIteratorExpressions();

  return 0;
}

/*
 * $ g++ -o main chapter-04/exercise-20.cc && ./main
 * Case (a) *iter++:
 *   Legal: Dereferences current iter, then increments
 *   Returns: "hello"
 *   Now points to: "world"
 *
 * Case (b) (*iter)++:
 *   Illegal: Cannot increment a string
 *
 * Case (c) *iter.empty():
 *   Illegal: Parses as *(iter.empty())
 *   Iterators don't have empty() method
 *
 * Case (d) iter->empty():
 *   Legal: Calls empty() on current string
 *   Current string empty? no
 *
 * Case (e) ++*iter:
 *   Illegal: Cannot increment a string
 *
 * Case (f) iter++->empty():
 *   Legal: Calls empty() on current string, then increments
 *   Current string empty? no
 *   Now points to: "cpp"
 */