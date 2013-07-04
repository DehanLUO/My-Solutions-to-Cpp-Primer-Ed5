/*
 * Exercise 7.32: Define your own versions of Screen and Window_mgr in which
 * clear is a member of Window_mgr and a friend of Screen.
 */

#ifndef CHAPTER_07_EXERCISE_32_H_
#define CHAPTER_07_EXERCISE_32_H_

#include <ostream>  // std::ostream
#include <string>   // std::string
#include <vector>   // std::vector

// Forward declaration for Screen (needed for WindowMgr)
class Screen;

class WindowMgr {
 public:
  // location ID for each screen on window
  using ScreenIndex = std::vector<Screen>::size_type;
  /**
   * @brief Clears the contents of a specific screen
   * @param idx Index of screen to clear
   * Resets the specified screen's contents to all blanks.
   * Does nothing if index is out of range.
   * @note Friend of Screen class - can access private members
   */
  void Clear(ScreenIndex idx);

 private:
  std::vector<Screen> screens_;  // Collection of managed screens
};  // class WindowMrg

class Screen {
  // Grant WindowMgr::Clear access to private members
  friend void WindowMgr::Clear(ScreenIndex);

 public:
  // alternative way to declare a type member using a type alias
  using Pos = std::string::size_type;

 private:
  Pos cursor_;            // position of the cursor
  Pos height_;            // height of the screen
  Pos width_;             // width of the screen
  std::string contents_;  // the screen's contents

 public:
  /**
   * @brief Default constructor
   * Creates an empty screen (0x0 dimensions).
   */
  Screen() : Screen(0, 0, ' ') {}

  /**
   * @brief Dimensioned constructor (blank screen)
   * @param height Max index of rows (> 0)
   * @param width Max index of columns per row (> 0)
   *
   * Delegates to primary constructor with space (' ') as fill character
   */
  explicit Screen(Pos height, Pos width) : Screen(height, width, ' ') {}

  /**
   * @brief Primary constructor
   * @param height Max index of rows (> 0)
   * @param width Max index of columns per row (> 0)
   * @param fill Character to initialize all screen positions
   *
   * Initializes screen buffer with height*width copies of fill character
   */
  explicit Screen(Pos height, Pos width, char fill)
      : cursor_(0),
        height_(height + 1),
        width_(width + 1),
        contents_(height_ * width_, fill) {}

  /**
   * @brief Gets screen height
   * @return Total number of rows
   */
  Pos GetHeight() const { return height_; }

  /**
   * @brief Gets screen width
   * @return Number of columns per row
   */
  Pos GetWidth() const { return width_; }

  /**
   * @brief Gets current cursor position
   * @return Linear index of cursor position
   */
  Pos GetCursor() const { return cursor_; }

  /**
   * @brief Moves cursor to specified position
   * @param row Target row (0-based)
   * @param col Target column (0-based)
   * @return Reference to modified Screen object (for chaining)
   *
   * @note No bounds checking performed. Invalid positions cause undefined
   * behavior.
   */
  Screen& Move(Pos row,
               Pos col) {  // we can specify inline on the definition
    cursor_ = CalculatePosition(
        row, col);  // move cursor to the column within that row
    return *this;   // return this object as an lvalue
  }

  /**
   * @brief Set character at current cursor position
   * @param word Character sets at current cursor position
   * @return Reference to modified Screen object (for chaining)
   */
  Screen& Set(char word) {
    contents_[cursor_] = word;
    return *this;
  }

  /**
   * @brief Set character at specified position
   * @param row Target row (0-based)
   * @param col Target column (0-based)
   * @param word Character sets at specified position
   * @return Reference to modified Screen object (for chaining)
   *
   * @note No bounds checking performed. Invalid positions cause undefined
   * behavior.
   */
  Screen& Set(Pos row, Pos col, char word) {
    contents_[CalculatePosition(row, col)] = word;
    return *this;  // return this object as an lvalue
  }

  /**
   * @brief Gets character at current cursor position
   * @return Character at cursor
   */
  char Get() const {            // get the character at the cursor
    return contents_[cursor_];  // implicitly inline
  }

  /**
   * @brief Gets character at specified position
   * @param row Target row (0-based)
   * @param col Target column (0-based)
   * @return Character at given coordinates
   *
   * @note No bounds checking performed. Invalid positions cause undefined
   * behavior.
   */
  char Get(Pos row, Pos col) const {  // declared as inline in the class
    return contents_[CalculatePosition(row, col)];  // return character at the
                                                    // given column
  };

  /**
   * @brief Renders screen contents to output stream
   * @param output_stream Target output stream
   * @return Reference to modified Screen object (for chaining)
   *
   * Output format:
   * - Each row on separate line
   * - No additional formatting or line endings
   */
  Screen& Display(std::ostream& output_stream) {
    DoDisplay(output_stream);
    return *this;
  }

  /**
   * @brief Renders screen contents to output stream
   * @param output_stream Target output stream
   * @return Constant reference to modified Screen object (for chaining)
   *
   * Output format:
   * - Each row on separate line
   * - No additional formatting or line endings
   */
  const Screen& Display(std::ostream& output_stream) const {
    DoDisplay(output_stream);
    return *this;
  }

 private:
  /**
   * @brief Calculates linear position from row/col coordinates
   * @param row Row number (0-based)
   * @param col Column number (0-based)
   * @return Linear position in contents_
   */
  Pos CalculatePosition(Pos row, Pos col) const { return (row * width_) + col; }

  /**
   * @brief Internal screen rendering implementation
   * @param output_stream Target output stream
   *
   * Iterates through each row, writing its contents followed by newline
   */
  void DoDisplay(std::ostream& output_stream) const {
    for (Pos height = 0; height < height_; ++height) {
      output_stream << contents_.substr(height * width_, width_) << '\n';
    }
  }
};  // class Screen

void WindowMgr::Clear(ScreenIndex idx) {
  if (idx >= screens_.size()) return;

  // screen is a reference to the Screen we want to clear
  Screen& screen = screens_[idx];
  // reset the contents of that Screen to all blanks
  screen.contents_ = std::string(screen.height_ * screen.width_, ' ');
}

#endif  // CHAPTER_07_EXERCISE_32_H_
