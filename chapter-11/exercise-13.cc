/*
 * Exercise 11.13: There are at least three ways to create the pairs in the
 * program for the previous exercise. Write three versions of that program,
 * creating the pairs in each way. Explain which form you think is easiest to
 * write and understand, and why.
 */

#include <iostream>  // std::cin, std::cout
#include <string>    // std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

int main() {
  std::vector<std::pair<std::string, int>> pairs;
  std::string word;
  int number;

  std::cout << "Enter string-int pairs (e.g., 'John 25'). "
            << "Type 'done' when finished:\n";

  // Read input until "done" is entered or EOF
  while (std::cin >> word && word != "done") {
    if (std::cin >> number) {
      // Create pair and add to vector

      /*
       * Option 1 : Using emplace_back (Recommended Version)
       * - Most efficient (constructs pair directly in vector)
       * - Combines creation and insertion in one operation
       * - Requires understanding of emplacement
       */
      pairs.emplace_back(word, number);

      /*
       * Option 2: Using make_pair
       * - Most explicit about creating a pair
       * - Clear separation of pair creation from insertion
       * - Slightly more verbose
       */
      // pairs.push_back(std::make_pair(word, number));

      /*
       * Option 3: Using initializer list
       * - Most concise syntax
       * - Clean and modern C++ style
       * - Less explicit about pair creation
       */
      // pairs.push_back({word, number});
    } else {
      std::cerr
          << "Invalid input format. Expected string followed by integer.\n";
      std::cin.clear();  // Clear error state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // Skip bad input
    }
  }

  // Print the collected pairs
  std::cout << "\nCollected pairs:\n";
  for (const auto& pair : pairs) {
    std::cout << pair.first << ": " << pair.second << '\n';
  }

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-13.cc && ./main
 * Enter string-int pairs (e.g., 'John 25'). Type 'done' when finished:
 * John 25 done
 *
 * Collected pairs:
 * John: 25
 */
