/*
 * Exercise 11.12: Write a program to read a sequence of strings and ints,
 * storing each into a pair. Store the pairs in a vector.
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
      pairs.emplace_back(word, number);
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
 * $ g++ -o main chapter-11/exercise-12.cc && ./main
 * Enter string-int pairs (e.g., 'John 25'). Type 'done' when finished:
 * John 25 done
 *
 * Collected pairs:
 * John: 25
 */
