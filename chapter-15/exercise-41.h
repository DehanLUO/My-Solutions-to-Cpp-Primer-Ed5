/*
 * Exercise 15.41: Reimplement your classes to use built-in pointers to
 * Query_base rather than shared_ptrs. Remember that your classes will no longer
 * be able to use the synthesized copy-control members.
 */

#ifndef CHAPTER_15_EXERCISE_41_H_
#define CHAPTER_15_EXERCISE_41_H_

#include <iostream>  // std::ostream, std::cout
#include <memory>    // std::shared_ptr
#include <string>    // std::string

#include "../chapter-12/exercise-33.h"

/**
 * @class Query_base
 * @brief Abstract base class for all query types
 * @note Defines the interface for query operations
 */
class QueryBase {
  friend class Query;

 protected:
  using LineNo = TextQuery::LineNo;

  /**
   * @brief Virtual destructor for polymorphic cleanup
   */
  virtual ~QueryBase() = default;

 private:
  /**
   * @brief Pure virtual function for query evaluation
   * @param text_query The TextQuery object to evaluate against
   * @return Shared pointer to QueryResult
   * @note Not implemented in this exercise
   */
  virtual std::shared_ptr<QueryResult> Eval(const TextQuery &) const = 0;

  /**
   * @brief Pure virtual function for query representation
   * @return String representation of the query
   */
  virtual std::string Rep() const = 0;
};

/**
 * @class Query
 * @brief Interface class that manages a reference-counted QueryBase*
 */
class Query {
  friend Query operator~(const Query &);
  friend Query operator|(const Query &, const Query &);
  friend Query operator&(const Query &, const Query &);

 public:
  /**
   * @brief Constructor from string (creates WordQuery)
   * @param str The search string
   */
  explicit Query(const std::string &str);

  explicit Query(QueryBase *query_base);

  Query(const Query &other);  // Copy constructor

  Query(Query &&other) noexcept;  // Move constructor

  Query &operator=(const Query &rhs);  // Copy assignment

  Query &operator=(Query &&rhs) noexcept;  // Move assignment

  ~Query();

  /**
   * @brief Evaluate the query against TextQuery
   * @param text_query The TextQuery object to search
   * @return Pointer to QueryResult
   */
  std::shared_ptr<QueryResult> Eval(const TextQuery &text_query) const;

  /**
   * @brief Get string representation of the query
   * @return String representation
   */
  std::string Rep() const;

 private:
  void Release();

  QueryBase *query_base_;
  int *count_;
};

/**
 * @class WordQuery
 * @brief Concrete class for simple word searches
 * @note Represents a basic word query operation
 */
class WordQuery : public QueryBase {
  friend class Query;

 private:
  /**
   * @brief Private constructor
   * @param str The word to search for
   */
  explicit WordQuery(const std::string &str);

  /**
   * @brief Evaluate the word query
   * @param text_query The TextQuery object to search
   * @return Shared pointer to QueryResult
   */
  std::shared_ptr<QueryResult> Eval(const TextQuery &text_query) const override;

  /**
   * @brief Get string representation
   * @return The query word
   */
  std::string Rep() const override;

  std::string query_word_;  // The word to search for
};

/**
 * @class NotQuery
 * @brief Concrete class for NOT query operations
 * @note Represents the negation of another query
 */
class NotQuery : public QueryBase {
  friend Query operator~(const Query &);

  /**
   * @brief Private constructor
   * @param query The query to negate
   */
  explicit NotQuery(const Query &query);

  /**
   * @brief Evaluate the NOT query
   * @param text_query The TextQuery object to search
   * @return Shared pointer to QueryResult
   */
  std::shared_ptr<QueryResult> Eval(const TextQuery &text_query) const override;

  /**
   * @brief Get string representation
   * @return String representation with ~ operator
   */
  std::string Rep() const override;

  Query query_;  // The query to negate
};

/**
 * @class BinaryQuery
 * @brief Abstract base class for binary query operations
 * @note Provides common functionality for AND and OR operations
 */
class BinaryQuery : public QueryBase {
 protected:
  /**
   * @brief Protected constructor
   * @param lhs Left-hand side query
   * @param rhs Right-hand side query
   * @param sym Operator symbol for representation
   */
  BinaryQuery(const Query &lhs, const Query &rhs, std::string sym);

  /**
   * @brief Get string representation of binary operation
   * @return Formatted string representation
   */
  std::string Rep() const override;

  Query lhs_;
  Query rhs_;
  std::string op_sym_;
};

/**
 * @class AndQuery
 * @brief Concrete class for AND query operations
 * @note Represents the intersection of two queries
 */
class AndQuery : public BinaryQuery {
  friend Query operator&(const Query &, const Query &);

 private:
  /**
   * @brief Private constructor
   * @param left Left-hand side query
   * @param right Right-hand side query
   */
  AndQuery(const Query &left, const Query &right);

  std::string Rep() const override;

  /**
   * @brief Evaluate the AND query
   * @param text_query The TextQuery object to search
   * @return Shared pointer to QueryResult
   */
  std::shared_ptr<QueryResult> Eval(const TextQuery &text_query) const override;
};

/**
 * @class OrQuery
 * @brief Concrete class for OR query operations
 * @note Represents the union of two queries
 */
class OrQuery : public BinaryQuery {
  friend Query operator|(const Query &, const Query &);

  /**
   * @brief Private constructor
   * @param left Left-hand side query
   * @param right Right-hand side query
   */
  OrQuery(const Query &left, const Query &right);

  std::string Rep() const override;

  /**
   * @brief Evaluate the OR query
   * @param text_query The TextQuery object to search
   * @return Shared pointer to QueryResult
   */
  std::shared_ptr<QueryResult> Eval(const TextQuery &text_query) const override;
};

/* Query class implementation */

inline Query::Query(const std::string &str)
    : query_base_(new WordQuery(str)), count_(new int(1)) {
  std::cout << "Query::Query(const std::string& " << str << ") called\n";
}

inline Query::Query(QueryBase *query_base)
    : query_base_(query_base), count_(new int(1)) {}

inline Query::Query(const Query &other)
    : query_base_(other.query_base_), count_(other.count_) {
  ++*count_;
}

inline Query::Query(Query &&other) noexcept
    : query_base_(other.query_base_), count_(other.count_) {
  other.query_base_ = nullptr;
  other.count_ = nullptr;
}

inline Query &Query::operator=(const Query &rhs) {
  if (&rhs == this) return *this;

  Release();

  query_base_ = rhs.query_base_;
  count_ = rhs.count_;
  ++(*count_);

  return *this;
}

inline Query &Query::operator=(Query &&rhs) noexcept {
  if (&rhs == this) return *this;

  Release();

  query_base_ = rhs.query_base_;
  count_ = rhs.count_;

  rhs.query_base_ = nullptr;
  rhs.count_ = nullptr;

  return *this;
}

inline Query::~Query() { Release(); }

inline std::shared_ptr<QueryResult> Query::Eval(
    const TextQuery &text_query) const {
  std::cout << "Query::Eval(const TextQuery &text_query) called\n";
  return query_base_->Eval(text_query);
}

inline std::string Query::Rep() const {
  std::cout << "Query::";
  return query_base_->Rep();
}

inline void Query::Release() {
  if (0 != --*count_) return;

  delete query_base_;
  delete count_;
}

/**
 * @brief Output operator for Query objects
 * @param ostream Output stream
 * @param query Query object to output
 * @return Reference to output stream
 */
inline std::ostream &operator<<(std::ostream &ostream, const Query &query) {
  return ostream << query.Rep();
}

/* WordQuery class implementation */

inline WordQuery::WordQuery(const std::string &str) : query_word_(str) {
  std::cout << "WordQuery::WordQuery(const std::string& " << str
            << ") called\n";
}

inline std::shared_ptr<QueryResult> WordQuery::Eval(
    const TextQuery &text_query) const {
  std::cout << "WordQuery::eval(const TextQuery&) called\n";
  return text_query.Query(query_word_);
}

inline std::string WordQuery::Rep() const {
  std::cout << "WordQuery::rep() " << query_word_ << " called\n";
  return query_word_;
}

/* NotQuery class implementation */

inline NotQuery::NotQuery(const Query &query) : query_(query) {
  std::cout << "NotQuery::NotQuery(const Query &query) called\n";
}

inline std::shared_ptr<QueryResult> NotQuery::Eval(
    const TextQuery &text_query) const {
  std::cout << "NotQuery::eval(const TextQuery&) called\n";

  // virtual call to eval through the Query operand
  auto result = query_.Eval(text_query);

  // start out with an empty result set
  auto ret_lines = std::make_shared<std::set<LineNo>>();

  // we have to iterate through the lines on which our operand appears
  auto begin = result->Begin();
  auto end = result->End();

  // for each line in the input file, if that line is not in result
  // add that line number to ret_lines
  auto size = result->GetFile()->size();
  for (std::size_t line_number = 0; line_number != size; ++line_number) {
    // if we have not processed all the line in result
    // check whether this line is present
    if (begin == end || *begin != line_number) {
      ret_lines->insert(line_number);  // if not in result, add this line
    } else if (begin != end) {
      ++begin;  // otherwise get the next line number in result if there is one
    }
  }

  return std::make_shared<QueryResult>(Rep(), result->GetFile(), ret_lines);
}

inline std::string NotQuery::Rep() const {
  std::cout << "NotQuery::rep() called\n";
  return "~(" + query_.Rep() + ")";
}

/* BinaryQuery class implementation */

inline BinaryQuery::BinaryQuery(const Query &lhs, const Query &rhs,
                                std::string sym)
    : lhs_(lhs), rhs_(rhs), op_sym_(sym) {
  std::cout << "BinaryQuery::BinaryQuery(const Query &lhs, "
               "const Query &rhs, std::string sym) called\n";
}

inline std::string BinaryQuery::Rep() const {
  std::cout << "BinaryQuery::rep() called\n";
  return "(" + lhs_.Rep() + " " + op_sym_ + " " + rhs_.Rep() + ")";
}

/* AndQuery class implementation */

inline AndQuery::AndQuery(const Query &left, const Query &right)
    : BinaryQuery(left, right, "&") {
  std::cout
      << "AndQuery::AndQuery(const Query &left, const Query &right) called\n";
}

inline std::string AndQuery::Rep() const {
  std::cout << "AndQuery::";
  return BinaryQuery::Rep();
}

inline std::shared_ptr<QueryResult> AndQuery::Eval(
    const TextQuery &text_query) const {
  std::cout << "AndQuery::eval(const TextQuery&) called\n";

  auto left = lhs_.Eval(text_query);
  auto right = rhs_.Eval(text_query);

  // set to hold the intersection of left and right
  auto ret_lines = std::make_shared<std::set<LineNo>>();

  // writes the intersection of two ranges to a destination iterator
  // destination iterator in this call adds elements to ret_lines
  std::set_intersection(left->Begin(), left->End(),    //
                        right->Begin(), right->End(),  //
                        std::inserter(*ret_lines, ret_lines->begin()));

  return std::make_shared<QueryResult>(Rep(), left->GetFile(), ret_lines);
}

/* OrQuery class implementation */

inline OrQuery::OrQuery(const Query &left, const Query &right)
    : BinaryQuery(left, right, "|") {
  std::cout
      << "OrQuery::OrQuery(const Query &left, const Query &right) called\n";
}

inline std::string OrQuery::Rep() const {
  std::cout << "OrQuery::";
  return BinaryQuery::Rep();
}

inline std::shared_ptr<QueryResult> OrQuery::Eval(
    const TextQuery &text_query) const {
  std::cout << "OrQuery::eval(const TextQuery&) called\n";

  auto left = lhs_.Eval(text_query);
  auto right = rhs_.Eval(text_query);

  // copty the line numbers from the left-hand operand into the result set
  auto ret_lines =
      std::make_shared<std::set<LineNo>>(left->Begin(), left->End());
  // insert lines from the right-hand operand
  ret_lines->insert(right->Begin(), right->End());

  return std::make_shared<QueryResult>(Rep(), left->GetFile(), ret_lines);
}

/* Free function operators */

inline Query operator~(const Query &query) {
  return Query(new NotQuery(query));
}

inline Query operator&(const Query &lhs, const Query &rhs) {
  return Query(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs) {
  return Query(new OrQuery(lhs, rhs));
}

#endif  // CHAPTER_15_EXERCISE_41_H_
