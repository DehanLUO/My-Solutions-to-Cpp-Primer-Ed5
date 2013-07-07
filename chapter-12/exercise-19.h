/*
 * Exercise 12.19: Define your own version of StrBlobPtr and update your StrBlob
 * class with the appropriate friend declaration and begin and end members.
 */

#ifndef CHAPTER_12_EXERCISE_19_H_
#define CHAPTER_12_EXERCISE_19_H_

#include <cctype>            // size_t
#include <initializer_list>  // std::initializer_list
#include <memory>            // std::shared_ptr, std::weak_ptr
#include <stdexcept>         // std::runtime_error, std::out_of_range
#include <string>            // std::string
#include <vector>            // std::vector

class StrBlobPtr;  // forward declaration

/**
 * @brief A wrapper class for std::vector<std::string> with shared ownership
 *
 * StrBlob manages a std::vector<std::string> through a std::shared_ptr,
 * allowing multiple StrBlob objects to share the same underlying data.
 * Provides safe element access with bounds checking.
 */
class StrBlob {
  friend class StrBlobPtr;  // Friend declaration for exercise-19

 public:
  // Type alias for vector size type
  typedef std::vector<std::string>::size_type SizeType;

  /**
   * @brief Default constructor
   * Creates an empty StrBlob with a new underlying vector
   */
  StrBlob();

  /**
   * @brief Initializer list constructor
   * @param ilst Initializer list of strings to populate the StrBlob
   */
  StrBlob(std::initializer_list<std::string> ilst);

  /**
   * @brief Returns the number of elements in the StrBlob
   * @return The size of the underlying vector
   */
  SizeType Size() const;

  /**
   * @brief Checks if the StrBlob is empty
   * @return true if the StrBlob contains no elements, false otherwise
   */
  bool Empty() const;

  /**
   * @brief Adds an element to the end of the StrBlob
   * @param str The string to add
   */
  void PushBack(const std::string& str);

  /**
   * @brief Removes the last element of the StrBlob
   * @throws std::out_of_range if the StrBlob is empty
   */
  void PopBack();

  /**
   * @brief Accesses the first element (non-const version)
   * @return Reference to the first element
   * @throws std::out_of_range if the StrBlob is empty
   */
  std::string& Front();

  /**
   * @brief Accesses the first element (const version)
   * @return Const reference to the first element
   * @throws std::out_of_range if the StrBlob is empty
   */
  std::string& Front() const;

  /**
   * @brief Accesses the last element (non-const version)
   * @return Reference to the last element
   * @throws std::out_of_range if the StrBlob is empty
   */
  std::string& Back();

  /**
   * @brief Accesses the last element (const version)
   * @return Const reference to the last element
   * @throws std::out_of_range if the StrBlob is empty
   */
  std::string& Back() const;

  /**
   * @brief Accesses the element at specified index (non-const version)
   * @param idx Index of the element to access
   * @return Reference to the requested element
   * @throws std::out_of_range if idx is out of range
   */
  std::string& At(SizeType idx);

  /**
   * @brief Accesses the element at specified index (const version)
   * @param idx Index of the element to access
   * @return Const reference to the requested element
   * @throws std::out_of_range if idx is out of range
   */
  std::string& At(SizeType idx) const;

  /**
   * @brief Returns a StrBlobPtr pointing to the first element in the StrBlob
   * @return StrBlobPtr positioned at the first element
   * @throws std::out_of_range if the StrBlob is empty
   * @note Non-const version provides read-write access
   * @see End()
   */
  StrBlobPtr Begin();

  /**
   * @brief Returns a StrBlobPtr pointing one past the last element in the
   * StrBlob
   * @return StrBlobPtr positioned at the end marker
   * @note Can be compared with other StrBlobPtrs but cannot be dereferenced
   * @see Begin()
   */
  StrBlobPtr End();

 protected:
  /*
   * @brief Checks if the StrBlob is empty and throws if it is
   * @param msg The error message to include in the exception
   * @throws std::out_of_range if the StrBlob is empty
   */
  void Check(const std::string& msg) const;

  /**
   * @brief Template helper for accessing front element
   * @tparam VecType Type of vector (const or non-const)
   * @param vec The vector to access
   * @return Reference to the front element
   * @throws std::out_of_range if the vector is empty
   */
  template <typename VecType>
  static auto AccessFront(VecType& vec) -> decltype((vec.front()));

  /**
   * @brief Template helper for accessing back element
   * @tparam VecType Type of vector (const or non-const)
   * @param vec The vector to access
   * @return Reference to the back element
   * @throws std::out_of_range if the vector is empty
   */
  template <typename VecType>
  static auto AccessBack(VecType& vec) -> decltype((vec.back()));

  /**
   * @brief Template helper for accessing element at index
   * @tparam VecType Type of vector (const or non-const)
   * @param vec The vector to access
   * @param idx Index of the element to access
   * @return Reference to the requested element
   * @throws std::out_of_range if idx is out of range
   */
  template <typename VecType>
  static auto AccessAt(VecType& vec, SizeType idx) -> decltype((vec.at(idx)));

 private:
  // Shared pointer to the underlying vector of strings
  std::shared_ptr<std::vector<std::string>> data_;
};

/**
 * @brief Iterator-like class for StrBlob
 *
 * StrBlobPtr provides pointer-like operations for traversing a StrBlob.
 * It holds a weak_ptr to the underlying vector to avoid preventing its
 * deletion.
 */
class StrBlobPtr {
 public:
  /**
   * @brief Default constructor
   * Creates an invalid StrBlobPtr
   */
  StrBlobPtr();

  /**
   * @brief Constructs a StrBlobPtr pointing to the given StrBlob
   * @param blob The StrBlob to point to
   * @param idx The initial position (defaults to 0)
   */
  StrBlobPtr(StrBlob& blob, size_t idx = 0);

  /**
   * @brief Dereferences the pointer
   * @return Reference to the string at the current position
   * @throws std::runtime_error if the underlying vector has been freed
   * @throws std::out_of_range if the current position is invalid
   */
  std::string& Deref() const;

  /**
   * @brief Advances the pointer to the next element
   * @return Reference to the incremented StrBlobPtr
   * @throws std::runtime_error if the underlying vector has been freed
   * @throws std::out_of_range if already at end
   */
  StrBlobPtr& Incr();

  /**
   * @brief Equality comparison
   * @param other The other StrBlobPtr to compare with
   * @return true if both pointers point to the same vector and position
   */
  bool operator!=(const StrBlobPtr& other) const;

 private:
  /**
   * @brief Verifies that the pointer is still valid and the index is in range
   * @param idx The position to check
   * @param msg The error message to use if check fails
   * @return shared_ptr to the underlying vector if valid
   * @throws std::runtime_error if the vector has been freed
   * @throws std::out_of_range if the index is invalid
   */
  std::shared_ptr<std::vector<std::string>> Check(std::size_t idx,
                                                  const std::string& msg) const;

 private:
  // store a weak_ptr, which means the underlying vector might be destroyed
  std::weak_ptr<std::vector<std::string>> wptr_;
  std::size_t curr_;  // current position within tha array
};

// StrBlob implementation...
inline StrBlob::StrBlob()
    : data_(std::make_shared<std::vector<std::string>>()) {}

inline StrBlob::StrBlob(std::initializer_list<std::string> ilst)
    : data_(std::make_shared<std::vector<std::string>>(ilst)) {}

inline StrBlob::SizeType StrBlob::Size() const { return data_->size(); }

inline bool StrBlob::Empty() const { return data_->empty(); }

inline void StrBlob::PushBack(const std::string& str) { data_->push_back(str); }

inline void StrBlob::PopBack() {
  Check("pop_back on empty StrBlob");
  data_->pop_back();
}

inline std::string& StrBlob::Front() { return AccessFront(*data_); }

inline std::string& StrBlob::Front() const { return AccessFront(*data_); }

inline std::string& StrBlob::Back() { return AccessBack(*data_); }

inline std::string& StrBlob::Back() const { return AccessBack(*data_); }

inline std::string& StrBlob::At(SizeType idx) { return AccessAt(*data_, idx); }

inline std::string& StrBlob::At(SizeType idx) const {
  return AccessAt(*data_, idx);
}

inline StrBlobPtr StrBlob::Begin() { return StrBlobPtr(*this); }

inline StrBlobPtr StrBlob::End() { return StrBlobPtr(*this, data_->size()); }

inline void StrBlob::Check(const std::string& msg) const {
  if (data_->empty()) throw std::out_of_range(msg);
}

template <typename VecType>
auto StrBlob::AccessFront(VecType& vec) -> decltype((vec.front())) {
  if (vec.empty()) throw std::out_of_range("front on empty StrBlob");
  return vec.front();
}

template <typename VecType>
auto StrBlob::AccessBack(VecType& vec) -> decltype((vec.back())) {
  if (vec.empty()) throw std::out_of_range("back on empty StrBlob");
  return vec.back();
}

template <typename VecType>
auto StrBlob::AccessAt(VecType& vec, SizeType idx) -> decltype((vec.at(idx))) {
  if (idx >= vec.size()) throw std::out_of_range("at on empty StrBlob");
  return vec.at(idx);
}

// StrBlobPtr implementation...
inline StrBlobPtr::StrBlobPtr() : curr_(0) {}

inline StrBlobPtr::StrBlobPtr(StrBlob& blob, size_t idx)
    : wptr_(blob.data_), curr_(idx) {}

inline std::string& StrBlobPtr::Deref() const {
  auto ptr = Check(curr_, "dereference past end");
  return (*ptr)[curr_];  // (*p) is the vector to which this object points
}

inline StrBlobPtr& StrBlobPtr::Incr() {
  // if curr already points past the end of the container, can't increment it
  Check(curr_, "increment past end of StrBlobPtr");
  ++curr_;  // advance the current state
  return *this;
}

inline std::shared_ptr<std::vector<std::string>> StrBlobPtr::Check(
    std::size_t idx, const std::string& msg) const {
  auto ret = wptr_.lock();  // is the vector still around?
  if (!ret) {
    throw std::runtime_error("unbound StrBlobPtr");
  }
  if (idx >= ret->size()) {
    throw std::out_of_range(msg);
  }
  return ret;  // otherwise, return a shared_ptr to the vector
}

inline bool StrBlobPtr::operator!=(const StrBlobPtr& other) const {
  auto left = wptr_.lock();
  auto right = other.wptr_.lock();

  // If both weak_ptrs are expired, consider them equal
  if (!left && !right) return false;

  // If one is expired but not the other, they are not equal
  if (!left || !right) return true;

  // Compare vector addresses and current positions
  return left != right || curr_ != other.curr_;
}

#endif  // CHAPTER_12_EXERCISE_19_H_