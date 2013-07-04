/*
 * Exercise 7.42: For the class you wrote for exercise 7.40 in § 7.5.1 (p. 291),
 * decide whether any of the constructors might use delegation. If so, write the
 * delegating constructor(s) for your class. If not, look at the list of
 * abstractions and choose one that you think would use a delegating
 * constructor. Write the class definition for that abstraction.
 */

#ifndef CHAPTER_07_EXERCISE_42_H_
#define CHAPTER_07_EXERCISE_42_H_

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Represents a book in a library system
 */
class Book {
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
      : Book(title, author, isbn, 0, "", 0, 0) {}

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

#endif  // CHAPTER_07_EXERCISE_42_H_
