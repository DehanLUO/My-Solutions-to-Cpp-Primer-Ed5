/*
 * Exercise 15.38: Are the following declarations legal? If not, why not? If so,
 * explain what the declarations mean.
 *     BinaryQuery a = Query("fiery") & Query("bird");
 *     AndQuery b = Query("fiery") & Query("bird");
 *     OrQuery c = Query("fiery") & Query("bird");
 */

/*
 *              +------------------+
 *              |   Query_base     |  (Abstract)
 *              |------------------|
 *              | + eval() = 0     |
 *              | + rep()  = 0     |
 *              +------------------+
 *                      ▲
 *                      |
 *     ---------------------------------------------
 *     |                        |                  |
 * +-----------+         +---------------+   +---------------+
 * | WordQuery |         |  BinaryQuery  |   |  NotQuery     |
 * |-----------|         |---------------|   |---------------|
 * | word      |         | lhs, rhs      |   | query         |
 * | eval()    |         | rep() (impl.) |   | eval()        |
 * | rep()     |         | (virtual eval)|   | rep()         |
 * +-----------+         +---------------+   +---------------+
 *                              ▲
 *                -------------------------------
 *                |                             |
 *         +---------------+             +---------------+
 *         |   AndQuery    |             |   OrQuery     |
 *         |---------------|             |---------------|
 *         |eval()         |             | eval()        |
 *         +---------------+             +---------------+
 *
 *
 *                    +------------------+
 *                    |      Query       |   (instance)
 *                    |------------------|
 *                    | shared_ptr<      |
 *                    |   Query_base >   |
 *                    +------------------+
 */

#include "exercise-35-query.h"

int main() {
  /*
   * Illegal
   * BinaryQuery is an abstract base class (has pure virtual functions)
   * - Cannot instantiate abstract classes
   * - BinaryQuery::rep() is pure virtual in the actual implementation
   */
  // BinaryQuery a = Query("fiery") & Query("bird");

  /*
   * Illegal
   * operator& returns Query, not BinaryQuery
   * - Query("fiery") & Query("bird") returns a Query object
   * - Query cannot be converted to BinaryQuery
   */
  // AndQuery b = Query("fiery") & Query("bird");
  // OrQuery c = Query("fiery") & Query("bird");

  return 0;
}
