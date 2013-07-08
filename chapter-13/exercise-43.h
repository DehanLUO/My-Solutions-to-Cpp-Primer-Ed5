/*
 * Exercise 13.43: Rewrite the free member to use for_each and a lambda
 * (§ 10.3.2, p. 388) in place of the for loop to destroy the elements. Which
 * implementation do you prefer, and why?
 */

/*
 * Comparison of implementations:
 *
 * Original for-loop version advantages:
 * 1. More explicit control flow - clearly shows reverse iteration
 * 2. Slightly better performance (no function call overhead)
 * 3. More familiar to most C++ programmers
 * 4. Doesn't require reverse_iterator construction
 *
 * Lambda/for_each version advantages:
 * 1. More declarative style - shows intent rather than mechanism
 * 2. Better alignment with modern C++ practices
 * 3. More concise expression of the destruction operation
 * 4. Automatically handles iterator bounds checking
 *
 * Preferred implementation:
 * The original for-loop version is preferable for this specific case because:
 * 1. Memory management code benefits from explicit control flow
 * 2. The performance difference, while small, matters in low-level code
 * 3. The reverse destruction order is more immediately visible
 * 4. The lambda version requires additional iterator constructions
 *
 * However, the lambda version would be preferable in cases where:
 * 1. The operation was more complex
 * 2. We wanted to clearly separate the iteration from the operation
 * 3. We were working with forward iterators
 */

#ifndef CHAPTER_13_EXERCISE_43_H_
#define CHAPTER_13_EXERCISE_43_H_

#include <algorithm>  // std::for_each
#include <cstddef>    // size_t
#include <iterator>   // std::make_reverse_iterator
#include <string>     // std::string
#include <utility>    // std::pair

// simplified implementation of the memory allocation strategy for avector-like
// class
class StrVec {
 public:
  // the allocator member is default initialized
  StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {};
  StrVec(const StrVec &);               // copy constructor
  StrVec &operator=(const StrVec &);    // copy assignment
  ~StrVec();                            // destructor
  void push_back(const std::string &);  // copy the element
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string *begin() const { return elements; }
  std::string *end() const { return first_free; }
  // ...
 private:
  static std::allocator<std::string> alloc;  // allocates the elements
  void chk_n_alloc() {  // used by functions that add elements to a StrVec
    if (size() == capacity()) reallocate();
  }
  // utilities used by the copy constructor, assignment operator, and destructor
  std::pair<std::string *, std::string *> alloc_n_copy(const std::string *,
                                                       const std::string *);
  void free();        // destroy the elements and free the space
  void reallocate();  // get more space and copy the existing elements

 private:
  std::string *elements;    // pointer to the first element in the array
  std::string *first_free;  // pointer to the first free element in the array
  std::string *cap;         // pointer to one past the end of the array
};

// alloc must be defined in the StrVec implementation file
std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s) {
  chk_n_alloc();  // ensure that there is room for another element
  // construct a copy of s in the element to which first_free points
  alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(
    const std::string *b, const std::string *e) {
  // allocate space to hold as many elements as are in the range
  auto data = alloc.allocate(e - b);
  // initialize and return a pair constructed from date and the value returned
  // by uninitialized copy
  return {data, std::uninitialized_copy(b, e, data)};
}

/**
 * @brief Rewritten free() member using for_each and lambda
 * @post All elements are destroyed and memory is deallocated
 * @note Uses std::for_each with lambda to destroy elements
 */
void StrVec::free() {
  // may not pass deallocate a 0 pointer; if elements is 0, there's no work to
  // do
  if (elements) {
    // destroy the old elements in reverse order
    std::for_each(std::make_reverse_iterator(first_free),
                  std::make_reverse_iterator(elements),
                  [this](std::string &elem) { alloc.destroy(&elem); });
    alloc.deallocate(elements, cap - elements);
  }
}

StrVec::StrVec(const StrVec &s) {
  // call alloc_n_copy to allocate exactly as many elements as in s
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs) {
  // call alloc_n_copy to allocate exactly as many elements as in rhs
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

void StrVec::reallocate() {
  // we'll allocate space for twice as many elements as the current size
  auto newcapacity = size() ? 2 * size() : 1;
  // allocate new memeory
  auto newdata = alloc.allocate(newcapacity);
  // move the data from the old memeory to the new
  auto dest = newdata;   // points to the next free position in the new array
  auto elem = elements;  // points to the next element in the old array
  for (size_t i = 0; i != size(); ++i)
    alloc.construct(dest++, std::move(*elem++));
  free();  // free the old space once we've moved the elements
  // update our data structure to point to the new elements
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}

#endif  // CHAPTER_13_EXERCISE_43_H_
