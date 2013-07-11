/*
 * Exercise 15.36: Put print statements in the constructors and rep members and
 * run your code to check your answers to (a) and (b) from the first exercise.
 */

#include "exercise-35-query.h"

int main() {
  std::cout << "PART (a): CONSTRUCTOR EXECUTION SEQUENCE\n";
  Query q = Query("fiery") & Query("bird") | Query("wind");

  std::cout << "\nPART (b): rep() CALLS FROM cout << q\n";
  std::cout << q;

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-36.cc && ./main
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
 * Query::OrQuery::BinaryQuery::rep() called
 * Query::AndQuery::BinaryQuery::rep() called
 * Query::WordQuery::rep() fiery called
 * Query::WordQuery::rep() bird called
 * Query::WordQuery::rep() wind called
 * ((fiery & bird) | wind)
 */
