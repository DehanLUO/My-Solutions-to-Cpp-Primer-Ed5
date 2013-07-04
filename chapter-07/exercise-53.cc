/*
 * Exercise 7.53: Define your own version of Debug.
 */

class Debug {
 public:
  /**
   * @brief Default constructor enables all flags
   * @param b Initial value for all flags (default true)
   */
  constexpr Debug(bool b = true) : hw(b), io(b), other(b) {}

  /**
   * @brief Full constructor sets individual flags
   * @param h Hardware error flag
   * @param i I/O error flag
   * @param o Other errors flag
   */
  constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}

  /**
   * @brief Checks if any error flag is set
   * @return True if any flag is true
   */
  constexpr bool any() const noexcept { return hw || io || other; }

  // Flag setters (non-constexpr as they modify state)
  void set_io(bool b) { io = b; }
  void set_hw(bool b) { hw = b; }
  void set_other(bool b) { other = b; }

 private:
  bool hw;     // hardware errors
  bool io;     // I/O errors
  bool other;  // other errors
};

int main() {
  // Compile-time initialization
  constexpr Debug production(false);        // All flags disabled
  constexpr Debug test(true, false, true);  // Selective flags

  static_assert(!production.any(), "Production should have no errors");
  static_assert(test.any(), "Test should have errors");

  // Runtime usage
  Debug runtime_debug;
  runtime_debug.set_io(false);
  if (runtime_debug.any()) {
    // Handle errors
  }

  return 0;
}
