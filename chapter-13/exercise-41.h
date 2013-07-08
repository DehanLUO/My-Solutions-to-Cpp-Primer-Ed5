/*
 * Exercise 13.41: Why did we use postfix increment in the call to construct
 * inside push_back? What would happen if it used the prefix increment?
 */

#ifndef CHAPTER_13_EXERCISE_41_H_
#define CHAPTER_13_EXERCISE_41_H_

#include <cstddef>  // size_t
#include <string>   // std::string
#include <utility>  // std::pair

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

/*
 * Exercise 13.41: Postfix vs Prefix Increment in push_back
 *
 * The postfix increment (first_free++) is used in push_back's construct call
 * because:
 *
 * 1. Construction Semantics:
 *    - alloc.construct() needs the current value of first_free
 *    - The element should be constructed at the current first_free position
 *    - Only AFTER construction should first_free advance to next position
 *
 * 2. Sequence of Operations:
 *    With postfix increment (correct):
 *    a) construct() uses current first_free address
 *    b) first_free is incremented to next position
 *
 *    With prefix increment (incorrect):
 *    a) first_free would increment first
 *    b) construct() would use wrong (next) position
 *    c) Result: One position left unused, potential memory corruption
 *
 * 3. Safety Implications:
 *    - Postfix ensures proper construction before pointer advancement
 *    - Prefix could lead to:
 *      * Elements constructed in wrong locations
 *      * Memory leaks (unconstructed positions)
 *      * Potential buffer overflows
 *
 * 4. Performance Consideration:
 *    - While prefix is generally more efficient for primitives
 *    - For class types like iterators, difference is negligible
 *    - Correctness outweighs any micro-optimization here
 */
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

void StrVec::free() {
  // may not pass deallocate a 0 pointer; if elements is 0, there's no work to
  // do
  if (elements) {
    // destroy the old elements in reverse order
    for (auto p = first_free; p != elements; /* empty */) alloc.destroy(--p);
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

#endif  // CHAPTER_13_EXERCISE_41_H_
