/*
 * Exercise 13.40: Add a constructor that takes an initializer_list<string> to
 * your StrVec class.
 */

#ifndef CHAPTER_13_EXERCISE_40_ITERATOR_H_
#define CHAPTER_13_EXERCISE_40_ITERATOR_H_

#include <cstddef>   // std::ptrdiff_t
#include <iterator>  // std::random_access_iterator_tag

namespace my {

/**
 * @class Iterator
 * @brief Random access iterator for StrVec
 *
 * Provides iterator functionality for traversing and accessing elements
 * in the StrVec container. Models random access iterator requirements.
 */
template <typename T>
class Iterator {
 public:
  /* Type alias required for iterator traits*/
  using value_type = T;

  using pointer = value_type*;
  using reference = value_type&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::random_access_iterator_tag;

 public:
  /**
   * @brief Default constructor
   * @post Creates an invalid iterator pointing to nullptr
   */
  Iterator() : ptr_(nullptr) {}

  /**
   * @brief Construct from pointer
   * @param ptr Pointer to element
   * @post Iterator points to same element as ptr
   */
  explicit Iterator(pointer ptr) : ptr_(ptr) {}

  /* element access operations */
  pointer base() const { return ptr_; }
  reference operator*() const { return *ptr_; }
  pointer operator->() const { return ptr_; }
  reference operator[](difference_type n) const { return ptr_[n]; }

  /* Increment/decrement operations */
  Iterator& operator++() {
    ++ptr_;
    return *this;
  }
  Iterator& operator--() {
    --ptr_;
    return *this;
  }

  Iterator operator++(int) {
    Iterator temp(*this);
    ++(*this);
    return temp;
  }
  Iterator operator--(int) {
    Iterator temp(*this);
    --(*this);
    return temp;
  }

  /* Arithmetic operations */
  Iterator& operator+=(difference_type n) {
    ptr_ += n;
    return *this;
  }
  Iterator& operator-=(difference_type n) {
    ptr_ -= n;
    return *this;
  }

  Iterator operator+(difference_type n) const { return Iterator(ptr_ + n); }
  Iterator operator-(difference_type n) const { return Iterator(ptr_ - n); }

  /* Comparison operations */
  bool operator==(const Iterator& rhs) const { return ptr_ == rhs.ptr_; }
  bool operator<(const Iterator& rhs) const { return ptr_ < rhs.ptr_; }

  bool operator!=(const Iterator& rhs) const { return !(*this == rhs); }
  bool operator>(const Iterator& rhs) const { return rhs < *this; }
  bool operator>=(const Iterator& rhs) const { return !(*this < rhs); }
  bool operator<=(const Iterator& rhs) const { return !(rhs < *this); }

 private:
  pointer ptr_;  // Wrapped pointer to element
};

}  // namespace my

#endif  // CHAPTER_13_EXERCISE_40_ITERATOR_H_
