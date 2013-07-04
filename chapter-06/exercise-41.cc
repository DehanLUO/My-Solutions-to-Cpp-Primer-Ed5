/*
 * Exercise 6.41: Which, if any, of the following calls are illegal? Why? Which,
 * if any, are legal but unlikely to match the programmer’s intent? Why?
 * char *init(int ht, int wd = 80, char bckgrnd = ' ');
 *     (a) init();
 *     (b) init(24,10);
 *     (c) init(14, ’*’);
 */

/**
 * @brief Mock implementation of the Init function
 * @param ht Window height (mandatory)
 * @param wd Window width (default 80)
 * @param bckgrnd Background character (default ' ')
 * @return Pointer to initialized window buffer
 */

char* init(int ht, int wd = 80, char bckgrnd = ' ') {
  /*
   * Implementation notes:
   * - Parameters always received with these values:
   *   - ht: as provided
   *   - wd: provided or default 80
   *   - bckgrnd: provided or default ' '
   */
  static char buffer[256];
  // ... actual implementation would use parameters ...
  return buffer;
}

int main() {
  // Case (a) - Illegal: missing mandatory argument
  // init();
  /*
   * Violation:
   * - No value provided for mandatory 'ht' parameter
   * - Compiler error: too few arguments to function
   */

  // Case (b) - Legal and matches likely intent
  char* case_b = init(24, 10);
  /*
   * Behavior:
   * - ht = 24 (explicit)
   * - wd = 10 (explicit)
   * - bckgrnd = ' ' (default)
   * - Perfectly valid and clear call
   */

  // Case (c) - Legal but likely unintended
  char* case_c = init(14, '*');
  /*
   * Behavior:
   * - ht = 14 (explicit)
   * - wd = 42 (ASCII value of '*' implicitly converted to int)
   * - bckgrnd = ' ' (default)
   *
   * Problems:
   * 1. Character '*' implicitly converted to int (ASCII 42)
   * 2. Probably intended to set bckgrnd = '*'
   * 3. Correct version: Init(14, 80, '*')
   */

  return 0;
}