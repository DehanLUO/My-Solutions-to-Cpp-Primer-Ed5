/*
 * Exercise 15.34: For the expression built in Figure 15.3 (p. 638):
 *     (a) List the constructors executed in processing that expression.
 *     (b) List the calls to rep that are made from cout << q.
 *     (c) List the calls to eval made from q.eval().
 */

#include <iostream>  // std::ostream, std::cout
#include <memory>    // std::shared_ptr
#include <string>    // std::string

#include "../chapter-12/exercise-33.h"

// Forward declarations
class QueryBase;
class WordQuery;
class BinaryQuery;
class AndQuery;
class OrQuery;

class QueryBase {
  friend class Query;

 protected:
  using LineNo = TextQuery::LineNo;
  virtual ~QueryBase() = default;

 private:
  virtual std::shared_ptr<QueryResult> eval(const TextQuery &) const = 0;
  virtual std::string rep() const = 0;
};

class Query {
  friend Query operator~(const Query &);
  friend Query operator|(const Query &, const Query &);
  friend Query operator&(const Query &, const Query &);

 public:
  Query(const std::string &str);

  std::shared_ptr<QueryResult> eval(const TextQuery &text_query) const {
    std::cout << "Query::eval(const TextQuery &text_query) called\n";
    return query_base_->eval(text_query);
  }

  std::string rep() const {
    std::cout << "Query::rep() called\n";
    return query_base_->rep();
  }

 private:
  Query(std::shared_ptr<QueryBase> query) : query_base_(query) {
    std::cout << "Query::Query(std::shared_ptr<QueryBase> query)\n";
  }

  std::shared_ptr<QueryBase> query_base_;
};

std::ostream &operator<<(std::ostream &ostream, const Query &query) {
  return ostream << query.rep();
}

class WordQuery : public QueryBase {
  friend class Query;

  WordQuery(const std::string &str) : query_word_(str) {
    std::cout << "WordQuery::WordQuery(const std::string& " << str
              << ") called\n";
  }

  std::shared_ptr<QueryResult> eval(const TextQuery &text_query) const {
    std::cout << "WordQuery::eval(const TextQuery&) called\n";
    return text_query.Query(query_word_);
  }

  std::string rep() const {
    std::cout << "WordQuery::rep() called\n";
    return query_word_;
  }

  std::string query_word_;
};

Query::Query(const std::string &str) : query_base_(new WordQuery(str)) {
  std::cout << "Query::Query(const std::string& " << str << ") called\n";
}

class NotQuery : public QueryBase {
  friend Query operator~(const Query &operand) {
    return std::shared_ptr<QueryBase>(new NotQuery(operand));
  }

  NotQuery(const Query &query) : query_(query) {
    std::cout << "NotQuery::NotQuery(const Query &query) called\n";
  }

  std::shared_ptr<QueryResult> eval(const TextQuery &) const {
    std::cout << "NotQuery::eval(const TextQuery&) called\n";
  }

  std::string rep() const {
    std::cout << "NotQuery::rep() called\n";
    return "~(" + query_.rep() + ")";
  }

  Query query_;
};

class BinaryQuery : public QueryBase {
 protected:
  BinaryQuery(const Query &lhs, const Query &rhs, std::string sym)
      : lhs_(lhs), rhs_(rhs), op_sym_(sym) {
    std::cout << "BinaryQuery::BinaryQuery(const Query &lhs, "
                 "const Query &rhs, std::string sym) called\n";
  }

  std::string rep() const {
    std::cout << "BinaryQuery::rep() called\n";
    return "(" + lhs_.rep() + " " + op_sym_ + " " + rhs_.rep() + ")";
  }

  Query lhs_;
  Query rhs_;
  std::string op_sym_;
};

class AndQuery : public BinaryQuery {
  friend Query operator&(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
  }

  AndQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "&") {
    std::cout
        << "AndQuery::AndQuery(const Query &left, const Query &right) called\n";
  }

  std::string rep() const {
    std::cout << "AndQuery::rep() called\n";
    return BinaryQuery::rep();
  }

  std::shared_ptr<QueryResult> eval(const TextQuery &) const {
    std::cout << "AndQuery::eval(const TextQuery&) called\n";
  }
};

class OrQuery : public BinaryQuery {
  friend Query operator|(const Query &lhs, const Query &rhs) {
    return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
  }

  OrQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "|") {
    std::cout
        << "OrQuery::OrQuery(const Query &left, const Query &right) called\n";
  }

  std::string rep() const {
    std::cout << "OrQuery::rep() called\n";
    return BinaryQuery::rep();
  }

  std::shared_ptr<QueryResult> eval(const TextQuery &) const {
    std::cout << "OrQuery::eval(const TextQuery&) called\n";
  }
};

int main() {
  /*
   * Query(const std::string& fiery)
   *   WordQuery(const std::string& fiery)
   * Query(const std::string& bird)
   *   WordQuery(const std::string& bird)
   * BinaryQuery(fiery, bird, &)
   *   AndQuery(fiery, bird)
   * Query(std::shared_ptr<QueryBase>(AndQuery))
   * Query(const std::string& wind)
   *   WordQuery(const std::string& wind)
   * BinaryQuery(AndQuery, wind, |)
   *   OrQuery(AndQuery, wind)
   * Query(std::shared_ptr<QueryBase>(OrQuery))
   */
  std::cout << "PART (a): CONSTRUCTOR EXECUTION SEQUENCE\n";
  Query q = Query("fiery") & Query("bird") | Query("wind");

  /*
   * Query(OrQuery).rep() ->
   * OrQuery.rep() -> BinaryQuery.rep(): AndQuery.rep() + Query(Wind).rep()
   * Query(AndQuery).rep() ->
   * AndQuery.rep() -> BinaryQuery.rep(): Query(fiery).rep() + Query(bird).rep()
   * Query(fiery).rep() -> WordQuery(fiery).rep()
   * Query(bird).rep() -> WordQuery(bird).rep()
   * Query(wind).rep() -> WordQuery(wind).rep()
   */
  std::cout << "\nPART (b): rep() CALLS FROM cout << q\n";
  std::cout << q;

  /*
   * OrQuery::eval()
   *   → AndQuery::eval()
   *     → WordQuery::eval() for "fiery"
   *     → WordQuery::eval() for "bird"
   *   → WordQuery::eval() for "wind"
   */
  std::cout << "\nPART (c): eval() CALLS FROM q.eval()\n";
  // q.eval();
  std::cout << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-34.cc && ./main
 * PART (a): CONSTRUCTOR EXECUTION SEQUENCE
 * WordQuery::WordQuery(const std::string& fiery) called
 * Query::Query(const std::string& fiery) called
 * WordQuery::WordQuery(const std::string& bird) called
 * Query::Query(const std::string& bird) called
 * BinaryQuery::BinaryQuery(const Query &lhs, const Query &rhs, std::string sym) called
 * AndQuery::AndQuery(const Query &left, const Query &right) called
 * Query::Query(std::shared_ptr<QueryBase> query)
 * WordQuery::WordQuery(const std::string& wind) called
 * Query::Query(const std::string& wind) called
 * BinaryQuery::BinaryQuery(const Query &lhs, const Query &rhs, std::string sym) called
 * OrQuery::OrQuery(const Query &left, const Query &right) called
 * Query::Query(std::shared_ptr<QueryBase> query)
 *
 * PART (b): rep() CALLS FROM cout << q
 * Query::rep() called
 * OrQuery::rep() called
 * BinaryQuery::rep() called
 * Query::rep() called
 * AndQuery::rep() called
 * BinaryQuery::rep() called
 * Query::rep() called
 * WordQuery::rep() called
 * Query::rep() called
 * WordQuery::rep() called
 * Query::rep() called
 * WordQuery::rep() called
 * ((fiery & bird) | wind)
 */
