/*
 * Exercise 13.1: What is a copy constructor? When is it used?
 */

#include <iostream>  // std::cout
#include <string>    // std::string

/**
 * @brief Demonstrates copy constructor concepts
 *
 * A copy constructor is a special constructor that initializes a new object
 * as a copy of an existing object of the same type. It has the signature:
 *
 *     ClassName(const ClassName& other);
 *
 * Key characteristics:
 * 1. First parameter must be reference to const
 * 2. Typically takes const reference (but not required)
 * 3. Usually should not be explicit
 *
 * Usage contexts:
 * 1. When initializing an object from another of the same type
 * 2. When passing an object by value to a function
 * 3. When returning an object by value from a function
 * 4. When constructing elements in STL containers
 */
class Book {
  friend void ProcessBook(Book b);
  friend Book CreateBook();

 public:
  // Default constructor
  Book(const std::string& t = "", int p = 0) : title_(t), pages_(p) {
    std::cout << "CONSTRUCT default: " << title_ << ", " << pages_ << '\n';
  }

  // Copy constructor
  Book(const Book& other) : title_(other.title_), pages_(other.pages_) {
    std::cout << "CONSTRUCT copy: " << title_ << ", " << pages_ << '\n';
  }

 private:
  std::string title_;
  int pages_;
};

// Example function showing copy constructor usage
void ProcessBook(Book b) {  // Copy constructor invoked here
  std::cout << "Processing: " << b.title_ << "\n";
}

Book CreateBook() {
  Book temp("Temporary", 100);
  return temp;  // May invoke copy constructor (subject to copy elision)
}

int main() {
  std::cout << "1. Direct initialization through copy constructor\n";
  Book book1("C++ Primer", 500);

  std::cout << "Copy constructor called\n";
  Book book2 = book1;

  std::cout << "2. Pass by value - copy constructor invoked\n";
  ProcessBook(book1);

  std::cout << "3. Return by value - copy constructor may be invoked\n";
  Book book3 = CreateBook();

  std::cout << "4. Container operations\n";
  std::vector<Book> library;
  std::cout << "Copy constructor called via push_back\n";
  library.push_back(book1);

  return 0;
}

/*
 * $ g++ -o main chapter-13/exercise-01.cc && ./main
 * 1. Direct initialization through copy constructor
 * CONSTRUCT default: C++ Primer, 500
 * Copy constructor called
 * CONSTRUCT copy: C++ Primer, 500
 * 2. Pass by value - copy constructor invoked
 * CONSTRUCT copy: C++ Primer, 500
 * Processing: C++ Primer
 * 3. Return by value - copy constructor may be invoked
 * CONSTRUCT default: Temporary, 100
 * 4. Container operations
 * Copy constructor called via push_back
 * CONSTRUCT copy: C++ Primer, 500
 */
