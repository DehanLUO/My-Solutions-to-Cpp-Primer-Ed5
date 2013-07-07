/*
 * Exercise 12.32: Rewrite the TextQuery and QueryResult classes to use a
 * StrBlob instead of a vector<string> to hold the input file.
 */

#ifndef CHAPTER_12_EXERCISE_32_H_
#define CHAPTER_12_EXERCISE_32_H_

#include <cctype>    // ispunct, tolower
#include <cstddef>   // size_t
#include <iostream>  // std::istream, std::ostream
#include <map>       // std::map
#include <memory>    // std::shared_ptr, std::make_shared
#include <set>       // std::set
#include <sstream>   // std::istringstream
#include <string>    // std::string

#include "exercise-22.h"  // StrBlob

class QueryResult;  // Forward declaration

class TextQuery {
 public:
  using LineNo = size_t;
  using TextLines = StrBlob;
  using WordMap = std::map<std::string, std::set<LineNo>>;

  /**
   * @brief Constructs a TextQuery object from input stream
   * @param istream Input stream to process
   * @throws std::invalid_argument if any parameter is in invalid state
   * Time Complexity: O(n) where n is total words
   * Space Complexity: O(n) for text storage + O(m) for word index
   */
  explicit TextQuery(std::istream& istream);

  /**
   * @brief Executes a word query against stored text
   * @param word The search term to locate
   * @return shared_ptr to QueryResult containing matches
   * Time Complexity: O(log m) lookup + O(k) result construction
   * Space Complexity: O(k) for result storage
   */
  std::shared_ptr<QueryResult> Query(const std::string& word) const;

 protected:
  /**
   * @brief Normalizes a word by removing punctuation and converting to
   * lowercase.
   * @param word The input word
   * @return The word with all punctuation removed and letters converted to
   *         lowercase
   * Time Complexity: O(n), where n is the length of the input word
   * Space Complexity: O(n) for the returned string
   */
  static std::string FormatWord(const std::string& word);

 private:
  TextLines lines_;                    // Shared ownership of text
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
  QueryResult(std::string query_word, TextQuery::TextLines lines,
              std::shared_ptr<std::set<TextQuery::LineNo>> line_nums);

 private:
  std::string query_word_;
  TextQuery::TextLines lines_;
  std::shared_ptr<std::set<TextQuery::LineNo>> line_nums_;
};

/* TextQuery Implementation */

inline TextQuery::TextQuery(std::istream& istream)
    : word_map_(std::make_shared<WordMap>()) {
  if (!istream) {
    throw std::runtime_error("Invalid input stream");
  }

  std::string line;
  LineNo line_num = 0;

  /*
   * File processing loop:
   * 1. Reads each line into shared StrBlob
   * 2. Tokenizes words into map with line numbers
   * 3. Maintains 1-based line numbering for user output
   */
  while (std::getline(istream, line)) {
    lines_.PushBack(line);
    std::istringstream iss(line);
    std::string word;

    while (iss >> word) {
      (*word_map_)[FormatWord(word)].insert(line_num);
    }
    ++line_num;
  }
}

inline std::shared_ptr<QueryResult> TextQuery::Query(
    const std::string& word) const {
  static auto empty_line_nums = std::make_shared<std::set<LineNo>>();

  auto found = word_map_->find(FormatWord(word));
  if (found == word_map_->end()) {
    return std::make_shared<QueryResult>(word, lines_, empty_line_nums);
  }

  return std::make_shared<QueryResult>(
      word, lines_, std::make_shared<std::set<LineNo>>(found->second));
}

inline std::string TextQuery::FormatWord(const std::string& word) {
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
    std::string query_word, TextQuery::TextLines lines,
    std::shared_ptr<std::set<TextQuery::LineNo>> line_nums)
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
            << query_result.lines_.At(line_num) << '\n';
  }

  return ostream;
}

#endif  // CHAPTER_12_EXERCISE_32_H_