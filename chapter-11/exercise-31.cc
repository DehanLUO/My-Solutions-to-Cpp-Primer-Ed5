/*
 * Exercise 11.31: Write a program that defines a multimap of authors and their
 * works. Use find to find an element in the multimap and erase that element. Be
 * sure your program works correctly if the element you look for is not in the
 * map.
 */

#include <map>     // std::multimap
#include <string>  // std::string

/**
 * @brief Demonstrates multimap operations with author-work relationships
 * @param authors_to_find Container of author names to search and erase
 * @param kAuthorWorks Initial multimap containing author-work pairs
 */
void ProcessAuthorWorks(
    const std::multimap<std::string, std::string>& author_works,
    const std::vector<std::string>& authors_to_find) {
  /*
   * Multimap characteristics demonstrated:
   * - Allows duplicate keys (multiple works per author)
   * - Maintains sorted order by key
   * - find() returns first match for key
   */
  auto current_map = author_works;  // Working copy for modification

  for (const auto& author : authors_to_find) {
    /*
     * Critical sequence:
     * 1. find() locates first occurrence
     * 2. erase() removes found element
     * 3. Handles missing keys gracefully
     */
    auto found = current_map.find(author);

    if (found != current_map.end()) {
      // Successful find-erase operation
      current_map.erase(found);
      /*
       * Note about multimap erase behavior:
       * - Only removes single element at iterator
       * - For complete removal, use equal_range()
       */
    } else {
      // Graceful handling of missing keys
      /*
       * Important consideration:
       * - Failed searches return end() iterator
       * - No side effects when key not found
       */
    }
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
          {"Kafka", "The Metamorphosis"}};
}

int main() {
  const auto author_works = CreateTestMultimap();
  const std::vector<std::string> authors_to_process = {"Dostoevsky",
                                                       "Shakespeare"};

  ProcessAuthorWorks(author_works, authors_to_process);
  return 0;
}
