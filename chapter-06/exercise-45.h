/*
 * Exercise 6.45: Review the programs you’ve written for the earlier exercises
 * and decide whether they should be defined as inline. If so, do so. If not,
 * explain why they should not be inline.
 */

#include <string>  // std::string

// Exercise 6.41: Init function - Should NOT be inline
/**
 * @brief Initializes a window buffer with given parameters
 * @param ht Window height (mandatory)
 * @param wd Window width (default 80)
 * @param bckgrnd Background character (default ' ')
 * @return Pointer to initialized window buffer
 *
 * Not suitable for inlining because:
 * 1. Contains static local variable (buffer)
 * 2. Likely has non-trivial implementation in real usage
 * 3. Returns pointer to persistent storage
 */
char* Init(int ht, int wd = 80, char bckgrnd = ' ') {
  static char buffer[256];
  // Actual implementation would be more complex
  return buffer;
}

// Exercise 6.42: MakePlural function - GOOD candidate for inline
/**
 * @brief Returns plural version of word if count > 1 (inline)
 * @param count The quantity determining pluralization
 * @param word The base word to pluralize
 * @param ending The plural ending (default 's')
 * @return Pluralized string when count > 1, otherwise original word
 *
 * Suitable for inlining because:
 * 1. Simple one-line operation
 * 2. Frequently called in string processing
 * 3. No local variables or complex logic
 */
inline std::string MakePlural(size_t count, const std::string& word,
                              const std::string& ending = "s") {
  return (count > 1) ? word + ending : word;
}
