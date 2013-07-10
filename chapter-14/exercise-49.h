/*
 * Exercise 14.49: Regardless of whether it is a good idea to do so, define a
 * conversion to bool for the class from the previous exercise.
 */

#ifndef CHAPTER_14_EXERCISE_49_H_
#define CHAPTER_14_EXERCISE_49_H_

#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

/**
 * @brief Represents a book in a library system
 */
class Book {
  friend std::ostream& operator<<(std::ostream&, const Book&);

 public:
  /**
   * @brief Default constructs a blank book record
   * @post All string fields empty, numeric fields zero
   */
  Book() = default;

  /**
   * @brief Constructs with minimal identifying information
   * @param title The book's title
   * @param author The author's name
   * @param isbn Unique identifier (10 or 13 digits)
   */
  Book(const std::string& title, const std::string& author,
       const std::string& isbn)
      : title_(title), author_(author), isbn_(isbn) {}

  /**
   * @brief Constructs with complete metadata
   * @param title The book's title
   * @param author The author's name
   * @param isbn Unique identifier
   * @param pub_year Year of publication
   * @param genre Literary genre/category
   * @param pages Page count
   * @param copies Available copies
   */
  Book(const std::string& title, const std::string& author,
       const std::string& isbn, int pub_year, const std::string& genre,
       int pages, int copies)
      : title_(title),
        author_(author),
        isbn_(isbn),
        publication_year_(pub_year),
        genre_(genre),
        page_count_(pages),
        available_copies_(copies) {}

  /**
   * @brief Conversion operator to bool
   * @return True if the book object is valid/meaningful
   *
   * This conversion operator allows the Book object to be used in boolean
   * contexts, such as conditional statements. It should return true if
   * the book contains meaningful data (not a default-constructed empty book).
   *
   * The operator is declared explicit to prevent unintended implicit
   * conversions while still allowing explicit boolean checks.
   */
  explicit operator bool() const { return !title_.empty() && !isbn_.empty(); }

  /**
   * @brief Prints basic book information
   */
  void Display() const {
    std::cout << title_ << " by " << author_ << " (ISBN: " << isbn_ << ")\n";
  }

 private:
  std::string title_;
  std::string author_;
  std::string isbn_;
  int publication_year_ = 0;
  std::string genre_;
  int page_count_ = 0;
  int available_copies_ = 0;
};

std::ostream& operator<<(std::ostream& ostream, const Book& book) {
  return ostream << book.title_ << ' '             //
                 << book.author_ << ' '            //
                 << book.isbn_ << ' '              //
                 << book.publication_year_ << ' '  //
                 << book.genre_ << ' '             //
                 << book.page_count_ << ' '        //
                 << book.available_copies_;
}

#endif  // CHAPTER_14_EXERCISE_49_H_