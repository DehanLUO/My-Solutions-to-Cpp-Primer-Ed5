/*
 * Exercise 14.40: Rewrite the biggies function from § 10.3.2 (p. 391) to use
 * functionobject classes in place of lambdas.
 */

#include <algorithm>  // std::sort, std::stable_sort, std::unique, std::for_each
#include <iostream>   // std::cout
#include <string>     // std::string
#include <vector>     // std::vector

/**
 * @class SizeCompare
 * @brief Functor for comparing string lengths
 *
 * This function object compares two strings based on their lengths.
 * It is used for sorting strings by size while maintaining stability.
 */
class SizeCompare {
 public:
  /**
   * @brief Compares two strings by length
   * @param str1 First string to compare
   * @param str2 Second string to compare
   * @return bool True if str1 is shorter than str2
   * @time Complexity O(1) - constant time size comparison
   * @space Complexity O(1) - no additional space required
   */
  bool operator()(const std::string& str1, const std::string& str2) {
    return str1.size() < str2.size();
  }
};

/**
 * @class SizeLargerEqualThan
 * @brief Functor for checking if string length meets minimum threshold
 *
 * This function object checks whether a string's length is greater than
 * or equal to a specified minimum size.
 */
class SizeLargerEqualThan {
 public:
  /**
   * @brief Constructs a SizeLargerEqualThan with specified minimum size
   * @param size Minimum size threshold
   */
  explicit SizeLargerEqualThan(std::size_t size) : size_(size) {}

  /**
   * @brief Checks if string meets size requirement
   * @param str String to check
   * @return bool True if string size >= threshold
   * @time Complexity O(1) - constant time size check
   * @space Complexity O(1) - no additional space required
   */
  bool operator()(const std::string& str) const { return str.size() >= size_; }

 private:
  std::size_t size_;  // Minimum size threshold
};

/**
 * @class PrintString
 * @brief Functor for printing strings with configurable separator
 *
 * This function object prints strings to an output stream with a
 * specified separator between elements.
 */
class PrintString {
 public:
  /**
   * @brief Constructs a PrintString with output stream and separator
   * @param ostream Output stream reference (default: std::cout)
   * @param separator Character separator between strings (default: space)
   */
  explicit PrintString(std::ostream& ostream = std::cout, char separator = ' ')
      : ostream_(ostream), separator_(separator) {}

  /**
   * @brief Prints a string followed by separator
   * @param str String to print
   * @time Complexity O(n) where n is string length
   * @space Complexity O(1) - no additional space required
   */
  void operator()(const std::string& str) { ostream_ << str << separator_; }

 private:
  std::ostream& ostream_;  // Reference to output stream
  char separator_;         // Separator character between outputs
};

/**
 * @brief Removes duplicates and sorts words alphabetically
 * @param words The vector of strings to process
 */
void EliminateDuplicates(std::vector<std::string>& words) {
  std::sort(words.begin(), words.end());
  auto end_unique = std::unique(words.begin(), words.end());
  words.erase(end_unique, words.end());
}

/**
 * @brief Prints words of given length or longer
 * @param words The vector of strings to process
 * @param sz Minimum length threshold for words to print
 *
 * Operation sequence:
 * 1. Remove duplicates and sort alphabetically
 * 2. Stable sort by length
 * 3. Find first word meeting length requirement
 * 4. Print qualifying words
 */
void Biggies(std::vector<std::string>& words,
             std::vector<std::string>::size_type sz) {
  // Step 1: Eliminate duplicates and sort alphabetically
  EliminateDuplicates(words);

  // Step 2: Stable sort by length, maintaining alphabetical order
  {
    SizeCompare size_compare;
    std::stable_sort(words.begin(), words.end(), size_compare);
  }

  // Step 3: Find first word with size >= sz
  SizeLargerEqualThan size_larger_equal_than(sz);
  auto first_long_word =
      std::find_if(words.begin(), words.end(), size_larger_equal_than);

  // Step 4: Count and print words meeting length requirement
  auto count = words.end() - first_long_word;
  std::cout << count << " words of length " << sz << " or longer:\n";

  PrintString print_string(std::cout);
  std::for_each(first_long_word, words.end(), print_string);
  std::cout << '\n';
}

int main() {
  // Test case
  std::vector<std::string> words = {"the",  "quick", "brown", "fox", "jumps",
                                    "over", "the",   "lazy",  "dog"};

  // Test with different length thresholds
  Biggies(words, 3);
  Biggies(words, 4);
  Biggies(words, 5);

  return 0;
}

/*
 * $ g++ -o main chapter-14/exercise-40.cc && ./main
 * 8 words of length 3 or longer:
 * dog fox the lazy over brown jumps quick
 * 5 words of length 4 or longer:
 * lazy over brown jumps quick
 * 3 words of length 5 or longer:
 * brown jumps quick
 */
