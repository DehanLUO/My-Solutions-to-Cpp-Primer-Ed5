/*
 * Exercise 5.12: Modify our vowel-counting program so that it counts the number
 * of occurrences of the following two-character sequences: ff, fl, and fi.
 */

#include <cctype>    // tolower(), isspace()
#include <iostream>  // std::cin, std::cout

// Tracks counts for each target sequence
struct SequenceCount {
  unsigned ff = 0;
  unsigned fl = 0;
  unsigned fi = 0;
};

/**
 * Processes character pairs to detect target sequences
 * @param prev - Previous character in stream
 * @param current - Current character in stream
 * @param counts - Reference to counter structure
 */
void CheckSequences(char prev, char current, SequenceCount& counts) {
  current = tolower(current);
  prev = tolower(prev);

  if (prev == 'f') {
    if (current == 'f')
      ++counts.ff;
    else if (current == 'l')
      ++counts.fl;
    else if (current == 'i')
      ++counts.fi;
  }
}

/**
 * Checks if character is a vowel (case-insensitive)
 * @param c - Character to check
 * @return True if vowel (a,e,i,o,u), false otherwise
 */
bool IsVowel(char c) {
  c = tolower(c);
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

/**
 * Checks if character is whitespace (space, tab, newline)
 * @param c - Character to check
 * @return True if whitespace, false otherwise
 */
bool IsSpecialWhitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

int main() {
  SequenceCount counts;  // Initialize all counters to 0
  char prev = '\0';      // Stores previous character
  char current;          // Stores current character

  std::cout << "Enter text (Ctrl+D to end): ";

  while (std::cin.get(current)) {  // Read until EOF
    if (prev != '\0') {            // Only check after first character
      CheckSequences(prev, current, counts);
    }
    prev = current;  // Update previous character
  }

  // Output formatted results
  std::cout << "Sequence Analysis:\n"
            << "ff: " << counts.ff << '\n'
            << "fl: " << counts.fl << '\n'
            << "fi: " << counts.fi << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-12.cc && ./main
 * Enter text (Ctrl+D to end): The quick brown fox jumps over the lazy dog.
 * Sequence Analysis:
 * ff: 0
 * fl: 0
 * fi: 0
 */
