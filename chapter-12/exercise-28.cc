/*
 * Exercise 12.28: Write a program to implement text queries without defining
 * classes to manage the data. Your program should take a file and interact with
 * a user to query for words in that file. Use vector, map, and set containers
 * to hold the data for the file and to generate the results for the queries.
 */

#include <cstdlib>   // EXIT_FAILURE, EXIT_SUCCESS
#include <fstream>   // std::ifstream
#include <iostream>  // std::cin, std::cout
#include <map>       // std::map
#include <set>       // std::set
#include <sstream>   // std::istringstream
#include <string>    // std::string
#include <vector>    // std::vector

/**
 * @brief Reads file contents and builds word index
 * @param filename Input file path
 * @param lines Output parameter for file lines
 * @param word_map Output parameter for word index
 * @return true if file was successfully processed
 * Time Complexity: O(n) where n is file size
 * Space Complexity: O(n) for text storage + O(m) for word index
 */
bool BuildTextIndex(const std::string& filename,
                    std::vector<std::string>& lines,
                    std::map<std::string, std::set<size_t>>& word_map) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    std::cerr << "Error opening file: " << filename << '\n';
    return false;
  }

  std::string line;
  size_t line_num = 0;
  while (std::getline(infile, line)) {
    lines.push_back(line);
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
      word_map[word].insert(line_num);
    }
    ++line_num;
  }
  return true;
}

/**
 * @brief Executes query and prints results
 * @param query_word Word to search for
 * @param lines Reference to stored file lines
 * @param word_map Reference to word index
 * Time Complexity: O(log m + k) where m is unique words, k is matches
 * Space Complexity: O(1) additional space
 */
void ExecuteQuery(const std::string& query_word,
                  const std::vector<std::string>& lines,
                  const std::map<std::string, std::set<size_t>>& word_map) {
  auto found = word_map.find(query_word);
  if (found == word_map.end()) {
    std::cout << "Word '" << query_word << "' not found\n";
    return;
  }

  std::cout << "Word '" << query_word << "' appears " << found->second.size()
            << " times:\n";

  for (auto line_num : found->second) {
    std::cout << "(line " << line_num + 1 << ") " << lines[line_num] << '\n';
  }
}

/**
 * @brief Implements interactive text query interface
 * @param argc Argument count
 * @param argv Argument vector
 * @return Program exit status
 * Time Complexity: O(n) for setup + O(q*(log m + k)) for q queries
 * Space Complexity: O(n) for text storage
 */
int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  std::vector<std::string> lines;
  std::map<std::string, std::set<size_t>> word_map;

  if (!BuildTextIndex(argv[1], lines, word_map)) {
    return EXIT_FAILURE;
  }

  /*
   * User interaction loop:
   * 1. Prompts for query word
   * 2. Processes until exit command
   * 3. Provides immediate feedback
   */
  while (true) {
    std::cout << "Enter word to search (q to quit): ";
    std::string query_word;
    if (!(std::cin >> query_word) || query_word == "q") {
      break;
    }

    ExecuteQuery(query_word, lines, word_map);
  }

  return EXIT_SUCCESS;
}

/*
 * $ g++ -o main chapter-12/exercise-28.cc && ./main data/storyDataFile
 * Enter word to search (q to quit): her
 * Word 'her' appears 2 times:
 * (line 3) through her hair, it looks almost alive,
 * (line 9) him to tell her more.
 * Enter word to search (q to quit): q
 */
