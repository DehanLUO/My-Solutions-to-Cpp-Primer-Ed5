/*
 * Exercise 15.35: Implement the Query and Query_base classes, including a
 * definition of rep but omitting the definition of eval.
 */

#ifndef CHAPTER_15_EXERCISE_35_QUERY_H_
#define CHAPTER_15_EXERCISE_35_QUERY_H_

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
 * @brief Interface class for query operations
 * @note Manages shared_ptr to Query_base objects and provides user interface
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

  /**
   * @brief Evaluate the query against TextQuery
   * @param text_query The TextQuery object to search
   * @return Shared pointer to QueryResult
   */
  std::shared_ptr<QueryResult> Eval(const TextQuery &text_query) const;

  /**
   * @brief Get string representation of the query
   * @return String representation
   */
  std::string Rep() const;

 private:
  /**
   * @brief Private constructor from shared_ptr
   * @param query Shared pointer to Query_base object
   * @note Used by friend operators to create new Query objects
   */
  Query(std::shared_ptr<QueryBase> query);

  std::shared_ptr<QueryBase> query_base_;
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
  std::shared_ptr<QueryResult> Eval(const TextQuery &) const override;

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
  std::shared_ptr<QueryResult> Eval(const TextQuery &) const override;
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
  std::shared_ptr<QueryResult> Eval(const TextQuery &) const override;
};

/* Query class implementation */

inline Query::Query(const std::string &str) : query_base_(new WordQuery(str)) {
  std::cout << "Query::Query(const std::string& " << str << ") called\n";
}

inline Query::Query(std::shared_ptr<QueryBase> query) : query_base_(query) {
  std::cout << "Query::Query(std::shared_ptr<QueryBase> query)\n";
}

inline std::shared_ptr<QueryResult> Query::Eval(
    const TextQuery &text_query) const {
  std::cout << "Query::Eval(const TextQuery &text_query) called\n";
  return query_base_->Eval(text_query);
}

inline std::string Query::Rep() const {
  std::cout << "Query::";
  return query_base_->Rep();
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
  // Implementation omitted as required
  return nullptr;
}

inline std::string WordQuery::Rep() const {
  std::cout << "WordQuery::rep() " << query_word_ << " called\n";
  return query_word_;
}

/* NotQuery class implementation */

inline NotQuery::NotQuery(const Query &query) : query_(query) {
  std::cout << "NotQuery::NotQuery(const Query &query) called\n";
}

inline std::shared_ptr<QueryResult> NotQuery::Eval(const TextQuery &) const {
  std::cout << "NotQuery::eval(const TextQuery&) called\n";
  // Implementation omitted as required
  return nullptr;
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

inline std::shared_ptr<QueryResult> AndQuery::Eval(const TextQuery &) const {
  std::cout << "AndQuery::eval(const TextQuery&) called\n";
  // Implementation omitted as required
  return nullptr;
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

inline std::shared_ptr<QueryResult> OrQuery::Eval(const TextQuery &) const {
  std::cout << "OrQuery::eval(const TextQuery&) called\n";
  // Implementation omitted as required
  return nullptr;
}

/* Free function operators */

inline Query operator~(const Query &query) {
  return std::shared_ptr<QueryBase>(new NotQuery(query));
}

inline Query operator&(const Query &lhs, const Query &rhs) {
  return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs) {
  return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

#endif  // CHAPTER_15_EXERCISE_35_QUERY_H_
