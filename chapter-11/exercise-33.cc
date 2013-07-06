/*
 * Exercise 11.33: Implement your own version of the word-transformation
 * program.
 */

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
  std::map<std::string, std::string> transformation_map;
  std::string key;
  std::string value;

  /*
   * File format requirements:
   * - Key is first word on line
   * - Value is remainder of line
   * - Minimum value length enforced
   */
  while (map_file >> key && std::getline(map_file, value)) {
    if (value.size() > 1) {
      transformation_map[key] = value.substr(1);  // Remove leading space
    } else {
      throw std::runtime_error("Malformed transformation rule for: " + key);
    }
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
 * $ g++ -o main chapter-11/exercise-33.cc && ./main data/rules data/text
 * where are you
 * why dont you send me a picture
 * okay? thanks! later
 */
