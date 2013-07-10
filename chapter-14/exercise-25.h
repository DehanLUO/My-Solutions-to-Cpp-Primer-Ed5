/*
 * Exercise 14.25: Implement any other assignment operators your class should
 * define. Explain which types should be used as operands and why.
 */

#ifndef CHAPTER_14_EXERCISE_25_H_
#define CHAPTER_14_EXERCISE_25_H_

#include <iomanip>   // std::quoted
#include <iostream>  // std::cout, std::ostream
#include <sstream>   // std::istringstream
#include <string>    // std::string

/**
 * @brief Represents a book in a library system
 */
class Book {
  friend bool operator==(const Book& lhs, const Book& rhs);
  friend bool operator!=(const Book& lhs, const Book& rhs);

  friend std::ostream& operator<<(std::ostream&, const Book&);
  friend std::istream& operator>>(std::istream&, Book&);

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

  Book& operator=(const Book& other) = default;
  Book& operator=(Book&& other) = default;

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

inline bool operator==(const Book& lhs, const Book& rhs) {
  return lhs.title_ == rhs.title_                           //
         && lhs.author_ == rhs.author_                      //
         && lhs.isbn_ == rhs.isbn_                          //
         && lhs.publication_year_ == rhs.publication_year_  //
         && lhs.genre_ == rhs.genre_                        //
         && lhs.page_count_ == rhs.page_count_              //
         && lhs.available_copies_ == rhs.available_copies_;
}

inline bool operator!=(const Book& lhs, const Book& rhs) {
  return !(lhs == rhs);
}

inline std::ostream& operator<<(std::ostream& ostream, const Book& book) {
  return ostream << book.title_ << ' '             //
                 << book.author_ << ' '            //
                 << book.isbn_ << ' '              //
                 << book.publication_year_ << ' '  //
                 << book.genre_ << ' '             //
                 << book.page_count_ << ' '        //
                 << book.available_copies_;
}

// Input operator with comprehensive error handling
inline std::istream& operator>>(std::istream& is, Book& book) {
  std::string line;

  // Read entire line for atomic operation
  if (!getline(is, line)) {
    is.setstate(std::ios::failbit);
    return is;
  }

  std::istringstream iss(line);
  std::string title, author, isbn, genre;
  int year, pages, copies;

  // Parse with quoted string handling
  if (!(iss >> std::quoted(title) >> std::quoted(author) >> std::quoted(isbn) >>
        year >> std::quoted(genre) >> pages >> copies)) {
    is.setstate(std::ios::failbit);
    return is;
  }

  // Validate fields
  if (pages < 0 || copies < 0) {
    is.setstate(std::ios::failbit);
    return is;
  }

  // Commit changes
  book.title_ = std::move(title);
  book.author_ = std::move(author);
  book.isbn_ = std::move(isbn);
  book.publication_year_ = year;
  book.genre_ = std::move(genre);
  book.page_count_ = pages;
  book.available_copies_ = copies;

  return is;
}

#endif  // CHAPTER_14_EXERCISE_25_H_