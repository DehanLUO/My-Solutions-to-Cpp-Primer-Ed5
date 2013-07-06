/*
 * Exercise 11.32: Using the multimap from the previous exercise, write a
 * program to print the list of authors and their works alphabetically.
 */

#include <iostream>  // std::cout
#include <map>       // std::multimap
#include <string>    // std::string

/**
 * @brief Prints all author-work pairs in alphabetical order
 * @param author_works Multimap containing author-work pairs to print
 */
void PrintAuthorsAlphabetically(
    const std::multimap<std::string, std::string>& author_works) {
  /*
   * Iteration guarantees:
   * - Elements processed in key-sorted order (ascending)
   * - Works per author maintain insertion order
   * - const iteration prevents modification
   */
  for (const auto& author_work : author_works) {
    /*
     * Output formatting considerations:
     * - Using '\n' instead of std::endl
     * - Simple space separator between elements
     * - No additional formatting for clarity
     */
    std::cout << author_work.first << ": " << author_work.second << '\n';
  }
}

/**
 * @brief Creates demonstration multimap of classical authors and works
 * @return Prepopulated multimap for testing
 */
std::multimap<std::string, std::string> CreateTestMultimap() {
  return {{"Dostoevsky", "Crime and Punishment"},
          {"Dostoevsky", "The Brothers Karamazov"},
          {"Tolstoy", "War and Peace"},
          {"Tolstoy", "Anna Karenina"},
          {"Kafka", "The Metamorphosis"},
          {"Austen", "Pride and Prejudice"},
          {"Orwell", "1984"}};
}

int main() {
  const auto author_works = CreateTestMultimap();
  PrintAuthorsAlphabetically(author_works);
  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-32.cc && ./main
 * Austen: Pride and Prejudice
 * Dostoevsky: Crime and Punishment
 * Dostoevsky: The Brothers Karamazov
 * Kafka: The Metamorphosis
 * Orwell: 1984
 * Tolstoy: War and Peace
 * Tolstoy: Anna Karenina
 */
