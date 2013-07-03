// Exercise 5.15: Explain each of the following loops. Correct any problems you
// detect.
//     (a) for (int ix = 0; ix != sz; ++ix) { /* . . . */ }
//         if (ix != sz)
//           // . . .
//     (b) int ix;
//         for (ix != sz; ++ix) { /* . . . */ }
//     (c) for (int ix = 0; ix != sz; ++ix, ++ sz) { /* . . . */ }

/**
 * @brief Demonstrates corrected loop constructs from Exercise 5.15
 * @param void
 * @return Execution status (0 for success)
 */
int DemonstrateLoops() {
  /* Case (a) Analysis:
   * Original issue: ix out of scope in if-statement
   * Resolution: Move declaration before loop or restructure
   * Key concept: Block scope duration
   */
  {
    constexpr int sz = 10;
    int ix;                        // Declaration moved outside loop scope
    for (ix = 0; ix != sz; ++ix) { /* ... */
    }
    if (ix != sz) {
      // Valid access - ix remains in scope
    }
  }

  /*
   * Case (b) Analysis:
   * Original issues:
   * 1. Missing initialization expression
   * 2. Improper semicolon placement
   * Resolution: Add proper initialization
   * Key concept: For-loop syntax requirements
   */
  {
    constexpr int sz = 10;
    int ix = 0;              // Required initialization added
    for (; ix != sz; ++ix) { /* ... */
    }
  }

  /* Case (c) Analysis:
   * Original issue: Simultaneous modification of counter and boundary
   * Resolution: Separate increment operations
   * Key concept: Loop invariant preservation
   */
  {
    int sz = 10;
    for (int ix = 0; ix != sz; ++ix) {
      /* ... */
      // ++sz removed from increment expression
    }
  }

  return 0;
}

/**
 * @brief Entry point for loop demonstration
 * @param void
 * @return Program status code
 */
int main() {
  DemonstrateLoops();
  return 0;
}

/*
 * $ g++ -o main chapter-05/exercise-01.cc && ./main

 */
