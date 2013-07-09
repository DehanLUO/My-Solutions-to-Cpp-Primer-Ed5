/*
 * Exercise 14.7: Define an output operator for you String class you wrote for
 * the exercises in § 13.5 (p. 531).
 */

#ifndef CHAPTER_14_EXERCISE_07_H_
#define CHAPTER_14_EXERCISE_07_H_

#include <cstdint>    // UINT32_MAX
#include <cstring>    // std::memcpy
#include <iostream>   // std::ostream
#include <memory>     // std::allocator, std::allocator_traits
#include <stdexcept>  // std::logic_error
#include <utility>    // std::move

#include "../chapter-13/exercise-40-iterator.h"  // Iterator

namespace my {

/**
 * @class String
 * @brief Custom string class with allocator-based memory management
 *
 * Provides simplified string functionality similar to std::string,
 * using std::allocator for memory management and maintaining
 * null-termination for C-string compatibility.
 */
class String {
 public:
  /* Standard type aliases */
  using value_type = char;

  using allocator_type = std::allocator<value_type>;
  using alloc_traits = std::allocator_traits<allocator_type>;

  using reference = value_type&;
  using const_reference = value_type const&;

  using size_type = typename allocator_type::size_type;
  using difference_type = typename allocator_type::difference_type;

  using pointer = typename alloc_traits::pointer;
  using const_pointer = typename alloc_traits::const_pointer;

  using iterator = Iterator<value_type>;
  using const_iterator = Iterator<value_type const>;

 public:
  /**
   * @brief Default constructor
   * @post Creates empty string with minimum capacity
   * @note No-throw guarantee
   */
  String()
      : size_(0), capacity_(kMinCap), data_(alloc_.allocate(capacity_ + 1)) {
    data_[size_] = '\0';
  }

  /**
   * @brief Construct from C-style string
   * @param str Null-terminated C-string to copy
   * @post String contains copy of input C-string
   * @throw std::bad_alloc on memory allocation failure
   */
  String(const_pointer str)
      : size_(std::strlen(str)),
        capacity_(std::max(size_, kMinCap)),
        data_(alloc_.allocate(capacity_ + 1)) {
    std::memcpy(data_, str, size_ + 1);  // Copy including null terminator
  }

  /**
   * @brief Copy constructor
   * @param other String to copy
   * @post New string contains copy of other's content
   * @throw std::bad_alloc on memory allocation failure
   */
  String(const String& other)
      : size_(other.size_),
        capacity_(other.capacity_),
        data_(alloc_.allocate(capacity_ + 1)) {
    std::memcpy(data_, other.data_, size_ + 1);
  }

  /**
   * @brief Copy assignment operator
   * @param rhs String to copy
   * @return Reference to this object
   * @post Contents replaced with copy of rhs
   * @throw std::bad_alloc on memory allocation failure
   * @note Strong exception safety guarantee
   */
  String& operator=(const String& rhs) {
    if (&rhs == this) return *this;
    String temp(rhs);  // Copy construct temporary
    swap(temp);
    return *this;
  }

  /**
   * @brief Destructor
   * @post All memory deallocated via allocator
   * @note No-throw guarantee
   */
  ~String() { deallocate(); }

  /* Capacity operations */
  size_type size() const { return size_; }
  size_type length() const { return size(); }
  size_type max_size() const { return kMaxCap; }
  size_type capacity() const { return capacity_; }
  bool empty() const { return 0 == size_; }

  /* Element access operations */
  value_type const* data() const { return data_; }
  const_pointer c_str() const { return data(); }
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference operator[](size_type pos) const { return data_[pos]; }
  reference at(size_type pos);              // TODO(dehan)
  const_reference at(size_type pos) const;  // TODO(dehan)
  reference front();                        // TODO(dehan)
  const_reference front() const;            // TODO(dehan)
  reference back();                         // TODO(dehan)
  const_reference back() const;             // TODO(dehan)

  /* Iterator operations */

  /* Modifier operations */
  void clear() {
    if (nullptr == data_) return;
    data_[0] = '\0';
    size_ = 0;
  }

  void resize(size_type size);                    // TODO(dehan)
  void resize(size_type size, value_type value);  // TODO(dehan)
  void reserve(size_type size);                   // TODO(dehan)
  void shrink_to_fit();                           // TODO(dehan)

  void swap(String& other) noexcept {
    using std::swap;
    swap(size_, other.size_);
    swap(capacity_, other.capacity_);
    swap(data_, other.data_);
  }

 private:
  iterator make_iterator(pointer ptr) { return iterator(ptr); }
  const_iterator make_iterator(const_pointer ptr) {
    return const_iterator(ptr);
  }

  void deallocate() {
    if (nullptr == data_) return;
    alloc_.deallocate(data_, capacity_ + 1);
  }

  /**
   * @brief Reallocate storage with new capacity
   * @param new_capacity Requested new capacity
   * @pre new_capacity >= size()
   * @post Capacity increased to at least new_capacity
   * @throw std::bad_alloc on memory allocation failure
   * @note Strong exception safety guarantee
   */
  void reallocate(size_type new_capacity) {
    new_capacity = std::max(new_capacity, kMinCap);

    pointer new_data = nullptr;
    try {
      new_data = alloc_.allocate(new_capacity + 1);
      std::memcpy(new_data, data_,
                  size_ + 1);  // Copy including null terminator
    } catch (...) {
      if (nullptr != new_data) alloc_.deallocate(new_data, new_capacity + 1);
    }

    deallocate();
    data_ = new_data;
    capacity_ = new_capacity;
  }

 private:
  /* Static constants */
  static constexpr size_type kMaxCap = UINT32_MAX;  // Static allocator instance
  static constexpr size_type kMinCap = 15;          // Minimum initial capacity

  /* Member variables */
  static allocator_type alloc_;  // Static allocator instance
  size_type size_;      // Current string length (excluding null terminator)
  size_type capacity_;  // Current allocated capacity
  pointer data_;        // Pointer to allocated storage (null-terminated)

  /**
   * @brief Output stream insertion operator
   * @param ostream Output stream to write to
   * @param str String to output
   * @return Reference to the output stream
   * @note No-throw guarantee
   * @details Writes the string's contents to the output stream
   * without any formatting or additional characters.
   */
  friend std::ostream& operator<<(std::ostream& ostream, const String& str) {
    return ostream << str.data();
  }
};

constexpr String::size_type String::kMinCap;
String::allocator_type String::alloc_;  // Static member initialization

}  // namespace my

#endif  // CHAPTER_14_EXERCISE_07_H_
