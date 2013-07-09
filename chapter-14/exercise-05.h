/*
 * Exercise 14.5: In exercise 7.40 from § 7.5.1 (p. 291) you wrote a sketch of
 * one of the following classes. Decide what, if any, overloaded operators your
 * class should provide.
 *     (a) Book     (b) Date     (c) Employee
 *     (d) Vehicle  (e) Object   (f) Tree
 */

#ifndef CHAPTER_14_EXERCISE_05_H_
#define CHAPTER_14_EXERCISE_05_H_

#include <iostream>  // std::cout, std::ostream
#include <string>    // std::string

/**
 * @brief Represents a book in a library system
 */
class Book {
  friend bool operator==(const Book&, const Book&);
  friend bool operator!=(const Book&, const Book&);

  friend bool operator<(const Book&, const Book&);
  friend std::ostream& operator<<(std::ostream&, const Book&);
  friend std::istream& operator>>(std::istream&, Book&);

  Book& operator+=(int copies);
  Book& operator-=(int copies);

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

/**
 * @brief Equality comparison based on ISBN
 * @param rhs Comparable book object
 * @return True if ISBNs match exactly
 * @note ISBN serves as unique identifier in library systems
 */
bool operator==(const Book& lhs, const Book& rhs) {
  return lhs.isbn_ == rhs.isbn_;
}

/**
 * @brief Inequality comparison complement
 */
bool operator!=(const Book& lhs, const Book& rhs) { return !(lhs == rhs); }

/**
 * @brief Less-than comparison for sorting
 * @param rhs Comparable book object
 * @return True if this should appear before rhs in ordered collections
 * @note Uses lexicographical title comparison by default
 */
bool operator<(const Book& lhs, const Book& rhs) {
  return lhs.title_ < rhs.title_;
}

/**
 * @brief Output stream operator
 * @param ostream Output stream target
 * @param book Book to serialize
 * @return Reference to output stream
 * @note Formats output for database storage
 */
std::ostream& operator<<(std::ostream& ostream, const Book& book) {
  return ostream << book.title_ << '\n'
                 << book.author_ << '\n'
                 << book.isbn_ << '\n'
                 << book.publication_year_;
}

/**
 * @brief Input stream operator
 * @param istream Input stream source
 * @param book Book to populate
 * @return Reference to input stream
 */
std::istream& operator>>(std::istream& istream, Book& book) {
  return istream >> book.title_ >> book.author_ >> book.isbn_ >>
         book.publication_year_ >> book.genre_ >> book.page_count_ >>
         book.available_copies_;
}

/**
 * @brief Compound addition for inventory management
 * @param copies Number of copies to add
 * @return Reference to modified book
 */
Book& Book::operator+=(int copies) {
  available_copies_ += copies;
  return *this;
}

/**
 * @brief Compound subtraction for checkouts/returns
 * @param copies Number of copies to remove
 * @return Reference to modified book
 * @throws std::underflow_error if result would be negative
 */
Book& Book::operator-=(int copies) {
  available_copies_ -= copies;
  return *this;
}

#endif  // CHAPTER_14_EXERCISE_05_H_