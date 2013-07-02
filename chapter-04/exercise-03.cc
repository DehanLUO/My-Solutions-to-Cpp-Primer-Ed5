/*
 * Exercise 4.3: Order of evaluation for most of the binary operators is left
 * undefined to give the compiler opportunities for optimization. This strategy
 * presents a trade-off between efficient code generation and potential pitfalls
 * in the use of the language by the programmer. Do you consider that an
 * acceptable trade-off? Why or why not?
 */

/*
 * The undefined evaluation order in c++ represents a reasonable trade-off
 * between performance and saftey. While it can lead to subtle bugs in edge
 * cases (like `f(++i, i++)`), the flexibility enables crucial compiler
 * optimizations that make c++ suitable for high-performance applications.
 *
 * The design choice reflects c++'s philosophy of trusting experienced
 * programmers to write clear code while allowing maximum hardware utilization.
 * The trade-off is justified because:
 * - Well-structured code naturally avoids evaluation order issues
 * - The performance benefits are substantial for system programming
 * - Modern style guides and static analyzers can flag dangerous patterns
 *
 * The standard could enforce stricter evaluation rules, but this would
 * eliminate optimization opportunities that make c++ competitive in
 * perfermance-critical domains. The current approach maintains c++'s position
 * as both a high-level abstraction language and an efficient systems language.
 */

#include <iostream>  // std::cout

int main() {
  // Example showing potential danger
  int i = 0;
  std::cout << i << ' ' << ++i << '\n';  // Undefined behaviour
  // Could output "0 1" or "1 1" depending on evaluation order

  // Example where optimization helps
  int a = 5, b = 10, c = 15;
  int result = (a * b) + (c * b);  // Compiler may choose best multiply order
  // May evaluate as (a + c) * b if more efficient

  return 0;
}