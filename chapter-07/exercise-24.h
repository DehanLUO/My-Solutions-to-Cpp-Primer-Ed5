/*
 * Exercise 7.24: Give your Screen class three constructors: a default
 * constructor; a constructor that takes values for height and width and
 * initializes the contents to hold the given number of blanks; and a
 * constructor that takes values for height, width, and a character to use as
 * the contents of the screen.
 */

#ifndef CHAPTER_07_EXERCISE_24_H_
#define CHAPTER_07_EXERCISE_24_H_

#include <ostream>  // std::ostream
#include <string>   // std::string

class Screen {
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
   */
  void Set(const char word) { contents_[cursor_] = word; }

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

#endif  // CHAPTER_07_EXERCISE_24_H_
