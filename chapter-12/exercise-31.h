/*
 * Exercise 12.31: What difference(s) would it make if we used a vector instead
 * of a set to hold the line numbers? Which approach is better? Why?
 */

/*
 * Insertion Performance:
 * - set: O(log n) per insertion
 * - vector: O(1) amortized for push_back, but requires post processing
 * Memory Usage:
 * - set: Typically uses more memory per element (tree nodes)
 * - vector: Contiguous storage, less overhead
 * Lookup Performance:
 * - set: O(log n) per lookup
 * - vector: O(1) random access after sorting
 * Duplicate Handling:
 * - set: Automatically prevents duplicates
 * - vector: Requires manual deduplication (sort + unique)
 *
 * Conclusion: While both approaches are valid, the set version does better
 */

#ifndef CHAPTER_12_EXERCISE_31_H_
#define CHAPTER_12_EXERCISE_31_H_

#include <algorithm>  // std::sort, std::unique
#include <cctype>     // ispunct, tolower
#include <cstddef>    // size_t
#include <iostream>   // std::istream, std::ostream
#include <map>        // std::map
#include <memory>     // std::shared_ptr, std::make_shared
#include <sstream>    // std::istringstream
#include <string>     // std::string
#include <vector>     // std::vector

class QueryResult;  // Forward declaration

class TextQueryVectorVersion {
 public:
  using LineNo = size_t;
  using TextLines = std::vector<std::string>;
  using WordMap =
      std::map<std::string, std::vector<LineNo>>;  // changed to vector

  /**
   * @brief Constructs a TextQueryVectorVersion object from input stream
   * @param istream Input stream to process
   * Time Complexity: O(n + u log d) where:
   *   - n = total words
   *   - u = unique words
   *   - d = duplicates per word
   * Space Complexity: O(n) for text + O(m) for word index (m >= u)
   */
  explicit TextQueryVectorVersion(std::istream& istream);

  /**
   * @brief Executes a word query against stored text
   * @param word The search term to locate
   * @return shared_ptr to QueryResult containing matches
   * Time Complexity: O(log u) lookup + O(1) access per result
   * Space Complexity: O(k) for result storage (k = matching lines)
   */
  std::shared_ptr<QueryResult> Query(const std::string& word) const;

 protected:
  /**
   * @brief Normalizes a word by removing punctuation and converting to
   *        lowercase.
   * @param word The input word
   * @return The word with all punctuation removed and letters converted to
   *         lowercase
   * Time Complexity: O(n), where n is the length of the input word
   * Space Complexity: O(n) for the returned string
   */
  static std::string FormatWord(const std::string& word);

 private:
  std::shared_ptr<TextLines> lines_;   // Shared ownership of text
  std::shared_ptr<WordMap> word_map_;  // Shared ownership of index
};

class QueryResult {
  friend std::ostream& PrintResults(std::ostream&, const QueryResult&);

 public:
  /**
   * @brief Encapsulates results of a text query operation
   * @param query_word The searched term
   * @param lines Shared pointer to source text lines
   * @param line_nums Shared pointer to matching line numbers
   * Time Complexity: O(k) for k matching lines
   * Space Complexity: O(k) for result storage
   */
  QueryResult(
      std::string query_word,
      std::shared_ptr<TextQueryVectorVersion::TextLines> lines,
      std::shared_ptr<std::vector<TextQueryVectorVersion::LineNo>> line_nums);

 private:
  std::string query_word_;
  std::shared_ptr<TextQueryVectorVersion::TextLines> lines_;
  std::shared_ptr<std::vector<TextQueryVectorVersion::LineNo>> line_nums_;
};

/* TextQueryVectorVersion Implementation */

inline TextQueryVectorVersion::TextQueryVectorVersion(std::istream& istream)
    : lines_(std::make_shared<TextLines>()),
      word_map_(std::make_shared<WordMap>()) {
  std::string line;
  LineNo line_num = 0;

  /*
   * File processing loop:
   * 1. Reads each line into shared vector
   * 2. Tokenizes words into map with line numbers
   * 3. Maintains 1-based line numbering for user output
   */
  while (std::getline(istream, line)) {
    lines_->push_back(line);
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
      (*word_map_)[FormatWord(word)].push_back(line_num);  // Simple push_back
    }
    ++line_num;
  }

  // Post-processing to remove duplicates
  for (auto& pair : *word_map_) {
    auto& vec = pair.second;
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
  }
}

inline std::shared_ptr<QueryResult> TextQueryVectorVersion::Query(
    const std::string& word) const {
  static auto empty_line_nums = std::make_shared<std::vector<LineNo>>();

  auto found = word_map_->find(FormatWord(word));
  if (found == word_map_->end()) {
    return std::make_shared<QueryResult>(word, lines_, empty_line_nums);
  }

  return std::make_shared<QueryResult>(
      word, lines_, std::make_shared<std::vector<LineNo>>(found->second));
}

inline std::string TextQueryVectorVersion::FormatWord(const std::string& word) {
  std::string ret;
  ret.reserve(word.size());

  for (char letter : word) {
    if (0 == ispunct(letter)) {
      ret += static_cast<char>(tolower(letter));
    }
  }

  return std::move(ret);
}

/* QueryResult Implementation */

inline QueryResult::QueryResult(
    std::string query_word,
    std::shared_ptr<TextQueryVectorVersion::TextLines> lines,
    std::shared_ptr<std::vector<TextQueryVectorVersion::LineNo>> line_nums)
    : query_word_(std::move(query_word)),
      lines_(std::move(lines)),
      line_nums_(std::move(line_nums)) {}

/**
 * @brief Formats query results for output stream
 * @param ostream Output stream to write results
 * @param query_result QueryResult to display
 * @return Reference to output stream
 * Time Complexity: O(k) for k matching lines
 * Space Complexity: O(1) additional space
 */
inline std::ostream& PrintResults(std::ostream& ostream,
                                  const QueryResult& query_result) {
  ostream << "Query Word: \"" << query_result.query_word_ << "\" found "
          << query_result.line_nums_->size() << " times\n";

  /*
   * Result formatting:
   * 1. Displays 1-based line numbers for user readability
   * 2. Preserves original line formatting including whitespace
   */
  for (auto line_num : *query_result.line_nums_) {
    ostream << "(line " << line_num + 1 << ") "
            << (*query_result.lines_)[line_num] << '\n';
  }

  return ostream;
}

#endif  // CHAPTER_12_EXERCISE_31_H_