/*
 * Exercise 15.42: Design and implement one of the following enhancements:
 *     (a) Print words only once per sentence rather than once per line.
 *     (b) Introduce a history system in which the user can refer to a previous
 *         query by number, possibly adding to it or combining it with another.
 *     (c) Allow the user to limit the results so that only matches in a given
 *         range of lines are displayed.
 */

#include <iostream>  // std::cin, std::cout

#include "exercise-39-query.h"

/**
 * @brief Output formatter for range-limited results
 * @param ostream Output stream to write results
 * @param query_result QueryResult to display
 * @param begin First line of display range (for context)
 * @param end Last line of display range (for context)
 * @return Reference to output stream
 * Time Complexity: O(k) for k matching lines
 * Space Complexity: O(1) additional space
 */
inline std::ostream& PrintResultsInRange(std::ostream& ostream,            //
                                         const QueryResult& query_result,  //
                                         TextQuery::LineNo begin,
                                         TextQuery::LineNo end) {
  /*
   * Result formatting:
   * 1. Displays 1-based line numbers for user readability
   * 2. Preserves original line formatting including whitespace
   */
  for (auto line_num : *query_result.line_nums_) {
    auto real_line_num = line_num + 1;
    if (real_line_num < begin || real_line_num > end) continue;
    ostream << "(line " << real_line_num << ") "
            << (*query_result.lines_)[line_num] << '\n';
  }

  return ostream;
}

int main() {
  TextQuery text_query(std::cin);

  Query q = Query("fiery") & Query("bird") | Query("wind");
  std::cout << '\n';

  auto result = q.Eval(text_query);
  std::cout << '\n';

  PrintResultsInRange(std::cout, *result, 1, 2);

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-42.cc && ./main
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
 * (line 2) Her Daddy says when the wind blows
 */
