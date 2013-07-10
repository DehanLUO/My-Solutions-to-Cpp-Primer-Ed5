/*
 * Exercise 14.23: Define an initializer_list assignment operator for your
 * version of the StrVec class.
 */

#ifndef CHAPTER_14_EXERCISE_23_STRVEC_H_
#define CHAPTER_14_EXERCISE_23_STRVEC_H_

#include <algorithm>  // std::max, std::swap, std::lexicographical_compare
#include <cstdint>    // UINT32_MAX
#include <initializer_list>  // std::initializer_list
#include <memory>  // std::allocator, std::allocator_traits, uninitialized_copy
#include <stdexcept>  // std::logic_error
#include <string>     // std::string
#include <utility>    // std::forward

#include "../chapter-13/exercise-40-iterator.h"  // Iterator

namespace my {

/**
 * @class StrVec
 * @brief Custom dynamic array for string objects
 *
 * Implements core functionality of std::vector<std::string> with:
 * - Manual memory management via std::allocator
 * - Strong exception safety guarantees
 * - Move semantics for efficient transfers
 */
class StrVec {
  friend bool operator==(const StrVec& lhs, const StrVec& rhs);
  friend bool operator!=(const StrVec& lhs, const StrVec& rhs);

  friend bool operator<(const StrVec& lhs, const StrVec& rhs);
  friend bool operator>(const StrVec& lhs, const StrVec& rhs);
  friend bool operator>=(const StrVec& lhs, const StrVec& rhs);
  friend bool operator<=(const StrVec& lhs, const StrVec& rhs);

 public:
  /* Standard type aliases */
  using value_type = std::string;

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
   * @post Creates empty StrVec with null pointers
   */
  StrVec() : begin_(nullptr), end_(nullptr), cap_end_(nullptr) {}

  /**
   * @brief Copy constructor
   * @param other StrVec to copy from
   * @post New StrVec has independent copy of all elements
   * @throw std::bad_alloc on memory allocation failure
   */
  StrVec(const StrVec& other) : StrVec() {
    reallocate(other.size());
    construct_at_end(other.begin_, other.end_);
  };

  /**
   * @brief Move constructor
   * @param other Source StrVec to move from
   * @post Transfers ownership of resources from other
   * @note noexcept qualified for compatibility with STL containers
   * Complexity O(1)
   * Complexity O(1)
   */
  StrVec(StrVec&& other) noexcept
      : begin_(other.begin_), end_(other.end_), cap_end_(other.cap_end_) {
    other.begin_ = other.end_ = other.cap_end_ = nullptr;
  };

  /**
   * @brief Constructs a StrVec from an initializer list of strings
   * @param ilist Initializer list of strings to copy into the container
   * @post Effects:
   *      - Allocates storage exactly sized for ilist elements
   *      - All elements from ilist are copy-constructed into allocated storage
   *      - Size and capacity equal ilist.size()
   * @note Exception safety:
   *      - If memory allocation fails, throws std::bad_alloc
   *      - If any string copy fails:
   *        * Destroys already constructed elements
   *        * Deallocates storage
   *        * Exception propagates to caller
   * @warning Not noexcept - may throw on allocation or element construction
   */
  StrVec(std::initializer_list<value_type> ilist) : StrVec() {
    reallocate(ilist.size());
    construct_at_end(ilist.begin(), ilist.end());
  }

  /**
   * @brief Assignment operator from an initializer list
   * @param ilist Initializer list of strings to assign
   * @post Effects:
   *      - Replaces current contents with elements from ilist
   *      - If ilist.size() > capacity():
   *        * Allocates new storage sized for ilist.size()
   *        * Copy-constructs elements into new storage
   *        * Swaps with temporary, providing strong exception safety
   *      - Otherwise:
   *        * Clears existing elements
   *        * Copy-constructs elements into existing storage
   *      - Size equals ilist.size()
   * @note Exception safety:
   *      - Provides strong guarantee if reallocation occurs (via copy-and-swap)
   *      - Provides basic guarantee if constructed in-place
   *      - May throw std::bad_alloc or std::bad_alloc-related exceptions,
   *        or exceptions from string copy construction
   * @warning Not noexcept - may throw on allocation or element construction
   * @complexity Time O(n), Space O(n) in case of reallocation
   */
  StrVec& operator=(std::initializer_list<value_type> ilist) {
    size_type ilist_size = ilist.size();
    if (ilist_size > capacity()) {
      StrVec temp;
      temp.reallocate(ilist_size);
      temp.construct_at_end(ilist.begin(), ilist.end());

      swap(temp);
    } else {
      clear();
      construct_at_end(ilist.begin(), ilist.end());
    }

    return *this;
  }

  /**
   * @brief Copy assignment operator
   * @param rhs Source StrVec to copy from
   * @return Reference to this
   * @post Contents replaced with copy of rhs; capacity not shrunk
   * @note Strong exception safety guarantee if reallocation is required,
   *       basic guarantee otherwise.
   */
  StrVec& operator=(const StrVec& rhs) {
    if (&rhs == this) return *this;

    size_type rhs_size = rhs.size();
    if (rhs_size > capacity()) {
      StrVec temp;
      temp.reallocate(rhs_size);
      temp.construct_at_end(rhs.begin_, rhs.end_);

      swap(temp);
    } else {
      clear();
      construct_at_end(rhs.begin_, rhs.end_);
    }

    return *this;
  }

  /**
   * @brief Move assignment operator
   * @param rhs Source StrVec to move from
   * @return Reference to this
   * @post Transfers ownership of resources from rhs
   * @note noexcept qualified for compatibility with STL containers
   * Time Complexity O(n) if needing to destroy existing elements
   * Space Complexity O(1)
   */
  StrVec& operator=(StrVec&& rhs) noexcept {
    if (&rhs == this) return *this;

    // Clean up existing resources
    clear();
    deallocate();

    // Transfer ownership
    begin_ = rhs.begin_;
    end_ = rhs.end_;
    cap_end_ = rhs.cap_end_;

    // Leave rhs in valid empty state
    rhs.begin_ = rhs.end_ = rhs.cap_end_ = nullptr;

    return *this;
  }

  /**
   * @brief Destructor
   * @post All contained strings destroyed and memory deallocated
   */
  ~StrVec() {
    clear();
    deallocate();
  }

  /* Capacity operations */
  size_type size() const { return end_ - begin_; }
  size_type capacity() const { return cap_end_ - begin_; }
  size_type max_size() const { return kMaxSize; }

  /* Element access operations */
  reference operator[](size_type pos) { return *(begin_ + pos); }
  const_reference operator[](size_type pos) const { return *(begin_ + pos); }

  /* Iterator operations */
  iterator begin() { return make_iterator(begin_); }
  const_iterator begin() const { return make_iterator(begin_); }

  iterator end() { return make_iterator(end_); }
  const_iterator end() const { return make_iterator(end_); }

  /* Modifier operations */
  void clear() {
    if (nullptr == begin_) return;
    while (end_ != begin_) alloc_.destroy(--end_);
  }

  /**
   * @brief Exchanges the contents of this StrVec with another
   *
   * Swaps the internal pointers between this and other. Does not
   * perform element-wise copy or move. Operates in constant time.
   *
   * @param other Another StrVec to swap with
   * @post This object and other have exchanged contents; all iterators,
   *       pointers, and references to elements become invalid.
   * @note noexcept to enable use in STL algorithms and exception-safe code
   */
  void swap(StrVec& other) noexcept {
    using std::swap;
    swap(begin_, other.begin_);
    swap(end_, other.end_);
    swap(cap_end_, other.cap_end_);
  }

  /**
   * @brief Reserve storage capacity
   * @param size Minimum capacity to reserve
   * @post Capacity at least new_capacity if successful
   * @throw std::length_error if new_capacity > max_size()
   * @throw std::bad_alloc on memory allocation failure
   * @note Strong exception safety guarantee
   */
  void reserve(size_type size) {
    if (size <= capacity()) return;

    if (size > max_size()) throw std::logic_error("StrVec");

    reallocate(size);
  }

  /**
   * @brief Resize container
   * @param size New container size
   * @post New elements are default-constructed
   * @throw std::bad_alloc on memory allocation failure
   * @note Basic exception safety guarantee
   */
  void resize(size_type size) {
    size_type current_size = this->size();
    if (current_size < size) {
      append(size - current_size);
    } else if (current_size > size) {
      destruct_at_end(begin_ + size);
    }
  }

  /**
   * @brief Resize container with value initialization
   * @param size New container size
   * @param value Value to initialize new elements
   * @post New elements are copies of value
   * @throw std::bad_alloc on memory allocation failure
   * @note Basic exception safety guarantee
   */
  void resize(size_type size, const_reference value) {
    size_type current_size = this->size();
    if (current_size < size) {
      append(size - current_size, value);
    } else if (current_size > size) {
      destruct_at_end(begin_ + size);
    }
  }

  /**
   * @brief Add element to end (copy version)
   * @param value Value to add
   * @post value is copied to end of container
   * @throw std::bad_alloc on memory allocation failure
   * @note Strong exception safety guarantee
   */
  void push_back(const_reference value) {
    ensure_capacity();
    construct_one_at_end(value);
  }

  /**
   * @brief Add element to end (move version)
   * @param value Value to add
   * @post value is moved to end of container
   * @throw std::bad_alloc on memory allocation failure
   * @note Strong exception safety guarantee
   */
  void push_back(value_type&& value) {
    ensure_capacity();
    construct_one_at_end(std::move(value));
  }

 private:
  /* Private helper functions with detailed contracts */

  iterator make_iterator(pointer ptr) { return iterator(ptr); }
  const_iterator make_iterator(const_pointer ptr) const {
    return const_iterator(ptr);
  }

  /**
   * @brief Deallocate storage
   * @pre All elements must have been destroyed
   * @post Memory returned to allocator, pointers set to null
   */
  void deallocate() {
    if (nullptr == begin_) return;

    alloc_.deallocate(begin_, capacity());
    begin_ = end_ = cap_end_ = nullptr;
  }

  /**
   * @brief Reallocate storage to new capacity
   * @param new_capacity New storage capacity
   * @pre new_capacity >= size()
   * @post Storage has new capacity, elements moved to new location
   * @throw std::bad_alloc on memory allocation failure
   * @note Strong exception safety guarantee
   */
  void reallocate(size_type new_capacity) {
    // Allocate new memory block
    pointer new_begin = alloc_.allocate(new_capacity);
    pointer new_end = new_begin;

    // Move existing elements
    size_type new_size = 0;
    try {
      while (new_size < size()) {
        alloc_.construct(new_end++, std::move_if_noexcept(begin_[new_size]));
        ++new_size;
      }
    } catch (...) {
      // Cleanup on failure
      for (size_type index = 0; index < new_size; ++index) {
        alloc_.destroy(&new_begin[index]);
      }
      alloc_.deallocate(new_begin, new_capacity);
      throw;
    }

    // Cleanup old storage
    clear();
    deallocate();

    // Update pointers
    begin_ = new_begin;
    end_ = new_end;
    cap_end_ = begin_ + new_capacity;
  }

  /**
   * @brief Calculate recommended new capacity
   * @param new_size Requested minimum size
   * @return Recommended capacity
   * @throw std::logic_error if new_size exceeds max_size()
   */
  size_type recommend_size(size_type new_size) const {
    if (new_size > kMaxSize) throw std::logic_error("StrVec");

    const size_type current_capacity = capacity();
    if (current_capacity >= kMaxSize / 2) return kMaxSize;

    return std::max<size_type>(2 * current_capacity, new_size);
  }

  /**
   * @brief Check and expand capacity if needed
   * @post Ensures capacity >= size() + 1
   * @throw std::bad_alloc on memory allocation failure
   */
  void ensure_capacity() {
    if (end_ == cap_end_) reallocate(recommend_size(size() + 1));
  }

  /**
   * @brief Constructs default-initialized elements at the end of storage
   * @param nombre Number of elements to construct
   * @pre Sufficient unused capacity must be available (count <= capacity() -
   *      size())
   * @post 'count' default-constructed elements added at end
   * @note Caller must ensure capacity before invocation
   * @warning Undefined behaviour if precondition violated
   */
  void construct_at_end(size_type nombre) {
    for (size_type count = 0; count < nombre; ++count) {
      alloc_.construct(end_++);
    }
  }

  /**
   * @brief Constructs copy-initialized elements at the end of storage
   * @param nombre Number of elements to construct
   * @param value Const reference to source value for copying
   * @pre Sufficient unused capacity must be available (count <= capacity() -
   *      size())
   * @post 'count' copies of 'value' added at end
   * @note Caller must ensure capacity before invocation
   * @warning Undefined behaviour if precondition violated
   */
  void construct_at_end(size_type nombre, const_reference value) {
    for (size_type count = 0; count < nombre; ++count) {
      alloc_.construct(end_++, value);
    }
  }

  /**
   * @brief Constructs a range of elements at the end of storage using copy
   *        construction
   * @param first Pointer to the first element in source range
   * @param last Pointer to one past the last element in source range
   * @pre Must satisfy all conditions:
   *      - [first, last) must be a valid range
   *      - Sufficient unused capacity must be available
   * @post Effects:
   *      - Copies all elements from [first, last) to end of storage
   *      - end_ pointer advanced by nombre copied
   * @warning Undefined behaviour if:
   *      - Preconditions are violated
   *      - Ranges overlap
   */
  void construct_at_end(const_pointer first, const_pointer last) {
    end_ = std::uninitialized_copy(first, last, end_);
  }

  /**
   * @brief Destroy elements from given position to end
   * @param new_end Pointer to new end position
   * @pre new_end must be between begin_ and end_
   * @post Elements from new_end to end_ are destroyed
   */
  void destruct_at_end(pointer new_end) {
    while (end_ != new_end) alloc_.destroy(--end_);
  }

  /**
   * @brief Append default-constructed elements
   * @param nombre Number of elements to append
   * @post count elements added to end
   * @throw std::bad_alloc on memory allocation failure
   */
  void append(size_type nombre) {
    size_type current_size = this->size();
    if (nombre > max_size() - current_size) throw std::logic_error("StrVec");
    if (capacity() - current_size < nombre) reallocate(current_size + nombre);
    construct_at_end(nombre);
  }

  /**
   * @brief Append copies of value
   * @param nombre Number of elements to append
   * @param value Value to copy
   * @post count copies of value added to end
   * @throw std::bad_alloc on memory allocation failure
   */
  void append(size_type nombre, const_reference value) {
    size_type current_size = this->size();
    if (nombre > max_size() - current_size) throw std::logic_error("StrVec");
    if (capacity() - current_size < nombre) reallocate(current_size + nombre);
    construct_at_end(nombre, value);
  }

  /**
   * @brief Construct element at end (perfect forwarding)
   * @tparam Args Argument types
   * @param args Arguments to forward to constructor
   * @post New element constructed at end
   * @note Must have capacity available (call ensure_capacity first)
   */
  template <class... Args>
  void construct_one_at_end(Args&&... args) {
    alloc_.construct(end_++, std::forward<Args>(args)...);
  }

 private:
  /* Static constants */
  static constexpr size_type kMaxSize = UINT32_MAX;

  /* Member variables */
  static allocator_type alloc_;  // Static allocator instance
  pointer begin_;                // Start of allocated storage
  pointer end_;                  // End of used storage
  pointer cap_end_;              // End of allocated storage
};

// Static member initialization
StrVec::allocator_type StrVec::alloc_;

/**
 * @brief Equality comparison for StrVec objects
 * @param lhs Left-hand side StrVec
 * @param rhs Right-hand side StrVec
 * @return True if both StrVecs have identical size and element content
 * @TimeComplexity O(n) where n is the number of elements
 * @SpaceComplexity O(1)
 */
inline bool operator==(const StrVec& lhs, StrVec& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/**
 * @brief Less-than comparison for StrVec objects
 * @param lhs Left-hand side StrVec
 * @param rhs Right-hand side StrVec
 * @return True if lhs is lexicographically less than rhs
 *
 * Performs lexicographical comparison of the elements in both containers:
 * 1. Compares elements sequentially from beginning to end
 * 2. If all compared elements are equal, the shorter container is considered
 *    less
 * 3. Uses std::string's built-in comparison for individual element comparison
 *
 * @TimeComplexity O(min(n, m)) where n and m are the sizes of lhs and rhs
 * @SpaceComplexity O(1)
 */
inline bool operator<(const StrVec& lhs, const StrVec& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(),  //
                                      rhs.begin(), rhs.end());
}

/**
 * @brief Greater-than comparison for StrVec objects
 * @param lhs Left-hand side StrVec
 * @param rhs Right-hand side StrVec
 * @return True if lhs is lexicographically greater than rhs
 * @note Implemented in terms of less-than operator (rhs < lhs)
 * @TimeComplexity O(min(n, m)) where n and m are the sizes of lhs and rhs
 * @SpaceComplexity O(1)
 */
inline bool operator>(const StrVec& lhs, const StrVec& rhs) {
  return rhs < lhs;
}

/**
 * @brief Greater-than-or-equal comparison for StrVec objects
 * @param lhs Left-hand side StrVec
 * @param rhs Right-hand side StrVec
 * @return True if lhs is not lexicographically less than rhs
 * @note Implemented in terms of less-than operator
 * @TimeComplexity O(min(n, m)) where n and m are the sizes of lhs and rhs
 * @SpaceComplexity O(1)
 */
inline bool operator>=(const StrVec& lhs, const StrVec& rhs) {
  return !(lhs < rhs);
}

/**
 * @brief Less-than-or-equal comparison for StrVec objects
 * @param lhs Left-hand side StrVec
 * @param rhs Right-hand side StrVec
 * @return True if lhs is not lexicographically greater than rhs
 * @note Implemented in terms of less-than operator (rhs < lhs)
 * @TimeComplexity O(min(n, m)) where n and m are the sizes of lhs and rhs
 * @SpaceComplexity O(1)
 */
inline bool operator<=(const StrVec& lhs, const StrVec& rhs) {
  return !(rhs < lhs);
}

/**
 * @brief Inequality comparison for StrVec objects
 * @param lhs Left-hand side StrVec
 * @param rhs Right-hand side StrVec
 * @return True if StrVecs have different sizes or element content
 */
inline bool operator!=(const StrVec& lhs, const StrVec& rhs) {
  return !(lhs == rhs);
}

/**
 * @brief Specialization of std::swap for StrVec
 *
 * Enables ADL (argument-dependent lookup) and allows unqualified
 * swap(lhs, rhs) to work with std algorithms.
 *
 * @param lhs First StrVec
 * @param rhs Second StrVec
 * @post lhs and rhs exchange contents; iterators invalidated
 */
inline void swap(StrVec& lhs, StrVec& rhs) noexcept { lhs.swap(rhs); }

}  // namespace my

#endif  // CHAPTER_14_EXERCISE_23_STRVEC_H_