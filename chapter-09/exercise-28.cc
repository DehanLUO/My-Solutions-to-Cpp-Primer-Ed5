/*
 * Exercise 9.28: Write a function that takes a forward_list<string> and two
 * additional string arguments. The function should find the first string and
 * insert the second immediately following the first. If the first string is not
 * found, then insert the second string at the end of the list.
 */

#include <forward_list>  // std::forward_list
#include <iostream>      // std::cout
#include <string>        // std::string

/**
 * @brief Inserts a string after the first occurrence of another string in a
 * forward_list
 * @param flst The forward_list to modify
 * @param find_str The string to search for
 * @param insert_str The string to insert
 *
 * Behavior:
 * - If find_str is found, insert_str is inserted after it
 * - If find_str is not found, insert_str is appended to the end
 * - Maintains proper forward_list iterator safety
 */
void InsertAfterString(std::forward_list<std::string>& flst,
                       const std::string& find_str,
                       const std::string& insert_str) {
  auto prev = flst.before_begin();
  auto curr = flst.begin();

  // Traverse the list to find the target string
  while (curr != flst.end()) {
    if (*curr == find_str) {
      // Found the string - insert after current position
      flst.insert_after(curr, insert_str);
      return;
    }
    prev = curr;
    ++curr;
  }

  // String not found - insert at end
  flst.insert_after(prev, insert_str);
}

/**
 * @brief Prints the contents of a forward_list
 */
void PrintForwardList(const std::forward_list<std::string>& flst) {
  for (const auto& str : flst) {
    std::cout << str << ' ';
  }
  std::cout << '\n';
}

int main() {
  // Test case 1: String found in middle
  std::forward_list<std::string> words = {"apple", "banana", "cherry"};
  std::cout << "Before insertion: ";
  PrintForwardList(words);

  InsertAfterString(words, "banana", "blueberry");
  std::cout << "After inserting 'blueberry' after 'banana': ";
  PrintForwardList(words);

  // Test case 2: String not found
  InsertAfterString(words, "date", "orange");
  std::cout << "After inserting 'orange' (not found case): ";
  PrintForwardList(words);

  // Test case 3: Empty list
  std::forward_list<std::string> empty;
  InsertAfterString(empty, "anything", "first");
  std::cout << "After inserting into empty list: ";
  PrintForwardList(empty);

  return 0;
}

/*
 * $ g++ -o main chapter-09/exercise-28.cc && ./main
 * Before insertion: apple banana cherry
 * After inserting 'blueberry' after 'banana': apple banana blueberry cherry
 * After inserting 'orange' (not found case): apple banana blueberry cherry orange
 * After inserting into empty list: first
 */
