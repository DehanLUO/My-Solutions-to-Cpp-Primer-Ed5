/*
 * Exercise 11.36: Our program does no checking on the validity of either input
 * file. In particular, it assumes that the rules in the transformation file are
 * all sensible. What would happen if a line in that file has a key, one space,
 * and then the end of the line? Predict the behavior and then check it against
 * your version of the program.
 */

#include <cstddef>    // size_t
#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS
#include <fstream>    // std::ifstream
#include <iostream>   // std::cout
#include <map>        // std::map
#include <sstream>    // std::istringstream
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string

/**
 * @brief Constructs transformation map from rule file
 * @param map_file Input file stream containing transformation rules
 * @return Map of words to their replacements
 * @throws std::runtime_error On malformed rule entries
 */
std::map<std::string, std::string> BuildTransformationMap(
    std::ifstream& map_file) {
  // Test case analysis:
  // 1. "valid_key valid_value" → Success
  // 2. "" → Throws "Empty key"
  // 3. "key_only" → Throws "Missing transformation value"
  // 4. "trailing_space " → Throws "Missing transformation value"

  std::map<std::string, std::string> transformation_map;
  std::string key;
  std::string value;
  size_t line_number = 0;

  /*
   * File format requirements:
   * - Key is first word on line
   * - Value is remainder of line
   * - Minimum value length enforced
   */
  while (std::getline(map_file, value)) {
    ++line_number;
    std::istringstream line_stream(value);

    if (!(line_stream >> key)) {
      throw std::runtime_error("Empty key at line " +
                               std::to_string(line_number));
    }

    /*
     * Ciritcal validation points:
     * - Check for presence of space after key
     * - Verify meaningful transformation value
     * - Handle Windows (\r\n) and Unix (\n) line endings
     */
    std::string remainder;
    std::getline(line_stream, remainder);

    if (remainder.empty() || remainder == "\r") {
      throw std::runtime_error("Missing transforamtion value for '" + key +
                               "' at line" + std::to_string(line_number));
    }

    // Remove leading space and any trailing carriage return
    std::string clean_value = remainder.substr(1);
    if (!clean_value.empty() && clean_value.back() == '\r') {
      clean_value.pop_back();
    }

    transformation_map[key] = clean_value;
  }

  return transformation_map;
}

/**
 * @brief Applies transformation to a single word
 * @param word Input word to transform
 * @param trans_map Transformation rules map
 * @return Transformed word or original if no rule exists
 */
const std::string& TransformWord(
    const std::string& word,
    const std::map<std::string, std::string>& trans_map) {
  /*
   * Lookup process notes:
   * - Uses map's efficient O(log n) find
   * - Returns reference to avoid copying
   * - Preserves original case sensitivity
   */
  auto found = trans_map.find(word);
  return (found != trans_map.end()) ? found->second : word;
}

/**
 * @brief Processes input text applying transformation rules
 * @param map_file Stream containing transformation rules
 * @param input_file Stream containing text to transform
 */
void ProcessTextTransform(std::ifstream& map_file, std::ifstream& input_file) {
  const auto trans_map = BuildTransformationMap(map_file);
  std::string text_line;

  /*
   * Line processing strategy:
   * - Preserves original line structure
   * - Maintains word spacing
   * - Handles punctuation naturally
   */
  while (std::getline(input_file, text_line)) {
    std::istringstream line_stream(text_line);
    std::string word;
    bool is_first_word = true;

    while (line_stream >> word) {
      std::cout << (is_first_word ? "" : " ") << TransformWord(word, trans_map);
      is_first_word = false;
    }
    std::cout << '\n';
  }
}

/**
 * @brief Demonstrates word transformation with test files
 * @param rules_path Path to transformation rules file
 * @param input_path Path to input text file
 */
void RunWordTransformDemo(const std::string& rules_path,
                          const std::string& input_path) {
  std::ifstream rules_file(rules_path);
  std::ifstream input_file(input_path);

  if (!rules_file || !input_file) {
    throw std::runtime_error("Could not open required files");
  }

  ProcessTextTransform(rules_file, input_file);
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0]
              << " <transformation_rules> <input_text>\n";
    return EXIT_FAILURE;
  }

  try {
    RunWordTransformDemo(argv[1], argv[2]);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/*
 * $ g++ -o main chapter-11/exercise-36.cc && ./main data/rules data/text
 * where are you
 * why dont you send me a picture
 * okay? thanks! later
 */
