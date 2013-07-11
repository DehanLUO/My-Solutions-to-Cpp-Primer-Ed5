/*
 * Exercise 15.39: Implement the Query and Query_base classes. Test your
 * application by evaluating and printing a query such as the one in Figure 15.3
 * (p. 638).
 */

#include <iostream>  // std::cin, std::cout

#include "exercise-39-query.h"

int main() {
  TextQuery text_query(std::cin);

  Query q = Query("fiery") & Query("bird") | Query("wind");
  std::cout << '\n';

  auto result = q.Eval(text_query);
  std::cout << '\n';

  PrintResults(std::cout, *result);

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-39.cc && ./main
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
 * Query::Eval(const TextQuery &text_query) called
 * OrQuery::eval(const TextQuery&) called
 * Query::Eval(const TextQuery &text_query) called
 * AndQuery::eval(const TextQuery&) called
 * Query::Eval(const TextQuery &text_query) called
 * WordQuery::eval(const TextQuery&) called
 * Query::Eval(const TextQuery &text_query) called
 * WordQuery::eval(const TextQuery&) called
 * AndQuery::BinaryQuery::rep() called
 * Query::WordQuery::rep() fiery called
 * Query::WordQuery::rep() bird called
 * Query::Eval(const TextQuery &text_query) called
 * WordQuery::eval(const TextQuery&) called
 * OrQuery::BinaryQuery::rep() called
 * Query::AndQuery::BinaryQuery::rep() called
 * Query::WordQuery::rep() fiery called
 * Query::WordQuery::rep() bird called
 * Query::WordQuery::rep() wind called
 *
 * Query Word: "((fiery & bird) | wind)" found 3 times
 * (line 2) Her Daddy says when the wind blows
 * (line 4) like a fiery bird in flight.
 * (line 5) A beautiful fiery bird, he tells her,
 */
