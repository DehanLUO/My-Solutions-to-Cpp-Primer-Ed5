/*
 * Exercise 12.10: Explain whether the following call to the process function
 * defined on page 464 is correct. If not, how would you correct the call?
 *     shared_ptr<int> p(new int(42));
 *     process(shared_ptr<int>(p));
 */

#include <iostream>  // std::cout
#include <memory>    // std::shared_ptr

void process(std::shared_ptr<int> ptr) {
  // Use ptr - refcount increased during this function
  std::cout << "Inside process: use_count = " << ptr.use_count() << "\n";
}  // ptr destroyed here - refcount decreased

int main() {
  // Original implementation
  std::shared_ptr<int> p(new int(42));  // refcount = 1

  /*
   * The expression std::shared_ptr<int>(p) creates a temporary shared_ptr. This
   * performs a copy construction from p, increasing refcount to 2. The
   * temporary is then moved into the function parameter, maintaining refcount
   * at 2. Upon function exit, the parameter is destroyed, reducing refcount to
   * 1.
   */
  process(std::shared_ptr<int>(p));  // Creates temporary shared_ptr
  std::cout << "After process: use_count = " << p.use_count() << "\n";

  /* Recommended alternatives */
  // Option 1: Direct pass (preferred)
  process(p);

  // Option 2: make_shared initialization (optimal)
  auto p2 = std::make_shared<int>(42);
  process(p2);

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-10.cc && ./main
 * Inside process: use_count = 2
 * After process: use_count = 1
 * Inside process: use_count = 2
 * Inside process: use_count = 2
 */
