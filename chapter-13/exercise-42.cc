/*
 * Exercise 13.42: Test your StrVec class by using it in place of the
 * vector<string> in your TextQuery and QueryResult classes (§ 12.3, p. 484).
 */

#include <cctype>   // ispunct, tolower
#include <cstddef>  // size_t
#include <cstdlib>  // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream>  // std::ifstream
#include <iostream>  // std::cin, std::cout, std::cerr, std::istream, std::ostream
#include <map>       // std::map
#include <memory>    // std::shared_ptr, std::make_shared
#include <set>       // std::set
#include <sstream>  // std::istringstream
#include <string>   // std::string

#include "exercise-40.h"  // my::StrVec

class QueryResult;  // Forward declaration

class TextQuery {
 public:
  using LineNo = size_t;
  using TextLines = my::StrVec;
  using WordMap = std::map<std::string, std::set<LineNo>>;

  /**
   * @brief Constructs a TextQuery object from input stream
   * @param istream Input stream to process
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
  std::shared_ptr<TextLines> lines_;   // Shared ownership of text
  std::shared_ptr<WordMap> word_map_;  // Shared ownership of index
};

class QueryResult {
  friend std::ostream& PrintResults(std::ostream&, const QueryResult&);

 public:
  // Iterator types for line numbers
  using Iterator = std::set<TextQuery::LineNo>::iterator;
  using ConstIterator = std::set<TextQuery::LineNo>::const_iterator;

  /**
   * @brief Encapsulates results of a text query operation
   * @param query_word The searched term
   * @param lines Shared pointer to source text lines
   * @param line_nums Shared pointer to matching line numbers
   * Time Complexity: O(k) for k matching lines
   * Space Complexity: O(k) for result storage
   */
  QueryResult(std::string query_word,
              std::shared_ptr<TextQuery::TextLines> lines,
              std::shared_ptr<std::set<TextQuery::LineNo>> line_nums);

  /**
   * @brief Returns an iterator to the first matching line number
   * @return Iterator pointing to the beginning of line numbers set
   * @note Non-const version allows modification of line numbers
   * @see End()
   */
  Iterator Begin();

  /**
   * @brief Returns a const iterator to the first matching line number
   * @return ConstIterator pointing to the beginning of line numbers set
   * @note Const version provides read-only access
   * @see Cend()
   */
  ConstIterator Cbegin() const;

  /**
   * @brief Returns an iterator to the end of matching line numbers
   * @return Iterator pointing to one past the last line number
   * @note Cannot be dereferenced, used for range checking
   * @see Begin()
   */
  Iterator End();

  /**
   * @brief Returns a const iterator to the end of matching line numbers
   * @return ConstIterator pointing to one past the last line number
   * @note Cannot be dereferenced, used for range checking
   * @see Cbegin()
   */
  ConstIterator Cend() const;

  /**
   * @brief Provides access to the underlying text file storage
   * @return shared_ptr to the vector containing all text lines
   * @note Maintains shared ownership of the text data
   */
  std::shared_ptr<TextQuery::TextLines> GetFile() const;

 private:
  std::string query_word_;
  std::shared_ptr<TextQuery::TextLines> lines_;
  std::shared_ptr<std::set<TextQuery::LineNo>> line_nums_;
};

/* TextQuery Implementation */

inline TextQuery::TextQuery(std::istream& istream)
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
    std::string query_word, std::shared_ptr<TextQuery::TextLines> lines,
    std::shared_ptr<std::set<TextQuery::LineNo>> line_nums)
    : query_word_(std::move(query_word)),
      lines_(std::move(lines)),
      line_nums_(std::move(line_nums)) {}

inline QueryResult::Iterator QueryResult::Begin() {
  return line_nums_->begin();
}

inline QueryResult::ConstIterator QueryResult::Cbegin() const {
  return line_nums_->cbegin();
}

inline QueryResult::Iterator QueryResult::End() { return line_nums_->end(); }

inline QueryResult::ConstIterator QueryResult::Cend() const {
  return line_nums_->cend();
}

inline std::shared_ptr<TextQuery::TextLines> QueryResult::GetFile() const {
  return lines_;
}

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

void RunQueries(std::ifstream& infile) {
  TextQuery text_query(infile);  // Initialize query processor

  while (true) {
    std::cout << "Enter word to search (q to quit): ";
    std::string word;

    if (!(std::cin >> word) || word == "q") break;

    PrintResults(std::cout, *text_query.Query(word)) << '\n';
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return EXIT_FAILURE;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Error opening file: " << argv[1] << '\n';
    return EXIT_FAILURE;
  }

  RunQueries(input);

  return EXIT_SUCCESS;
}

/*
 * $ g++ -o main chapter-13/exercise-42.cc && ./main
 * Enter word to search (q to quit): her
 * Query Word: "her" found 4 times
 * (line 2) Her Daddy says when the wind blows
 * (line 3) through her hair, it looks almost alive,
 * (line 5) A beautiful fiery bird, he tells her,
 * (line 9) him to tell her more.
 *
 * Enter word to search (q to quit): q
 */
