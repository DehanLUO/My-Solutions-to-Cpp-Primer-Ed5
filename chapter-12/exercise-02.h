/*
 * Exercise 12.2: Write your own version of the StrBlob class including the
 * const versions of front and back.
 */

#ifndef CHAPTER_12_EXERCISE_02_H_
#define CHAPTER_12_EXERCISE_02_H_

#include <initializer_list>  // std::initializer_list
#include <memory>            // std::shared_ptr
#include <stdexcept>         // std::out_of_range
#include <string>            // std::string
#include <vector>            // std::vector

/**
 * @brief A wrapper class for std::vector<std::string> with shared ownership
 *
 * StrBlob manages a std::vector<std::string> through a std::shared_ptr,
 * allowing multiple StrBlob objects to share the same underlying data.
 * Provides safe element access with bounds checking.
 */
class StrBlob {
 public:
  // Type alias for vector size type
  typedef std::vector<std::string>::size_type SizeType;

  /**
   * @brief Default constructor
   * Creates an empty StrBlob with a new underlying vector
   */
  StrBlob() : data_(std::make_shared<std::vector<std::string>>()) {}

  /**
   * @brief Initializer list constructor
   * @param ilst Initializer list of strings to populate the StrBlob
   */
  StrBlob(std::initializer_list<std::string> ilst)
      : data_(std::make_shared<std::vector<std::string>>(ilst)) {}

  /**
   * @brief Returns the number of elements in the StrBlob
   * @return The size of the underlying vector
   */
  SizeType Size() const { return data_->size(); }

  /**
   * @brief Checks if the StrBlob is empty
   * @return true if the StrBlob contains no elements, false otherwise
   */
  bool Empty() const { return data_->empty(); }

  /**
   * @brief Adds an element to the end of the StrBlob
   * @param str The string to add
   */
  void PushBack(const std::string& str) { data_->push_back(str); }

  /**
   * @brief Removes the last element of the StrBlob
   * @throws std::out_of_range if the StrBlob is empty
   */
  void PopBack() {
    Check("pop_back on empty StrBlob");
    data_->pop_back();
  }

  /**
   * @brief Accesses the first element (non-const version)
   * @return Reference to the first element
   * @throws std::out_of_range if the StrBlob is empty
   */
  std::string& Front() { return AccessFront(*data_); }

  /**
   * @brief Accesses the first element (const version)
   * @return Const reference to the first element
   * @throws std::out_of_range if the StrBlob is empty
   */
  std::string& Front() const { return AccessFront(*data_); }

  /**
   * @brief Accesses the last element (non-const version)
   * @return Reference to the last element
   * @throws std::out_of_range if the StrBlob is empty
   */
  std::string& Back() { return AccessBack(*data_); }

  /**
   * @brief Accesses the last element (const version)
   * @return Const reference to the last element
   * @throws std::out_of_range if the StrBlob is empty
   */
  std::string& Back() const { return AccessBack(*data_); }

  /**
   * @brief Accesses the element at specified index (non-const version)
   * @param idx Index of the element to access
   * @return Reference to the requested element
   * @throws std::out_of_range if idx is out of range
   */
  std::string& At(SizeType idx) { return AccessAt(*data_, idx); }

  /**
   * @brief Accesses the element at specified index (const version)
   * @param idx Index of the element to access
   * @return Const reference to the requested element
   * @throws std::out_of_range if idx is out of range
   */
  std::string& At(SizeType idx) const { return AccessAt(*data_, idx); }

 protected:
  /*
   * @brief Checks if the StrBlob is empty and throws if it is
   * @param msg The error message to include in the exception
   * @throws std::out_of_range if the StrBlob is empty
   */
  void Check(const std::string& msg) const {
    if (data_->empty()) throw std::out_of_range(msg);
  }

  /**
   * @brief Template helper for accessing front element
   * @tparam VecType Type of vector (const or non-const)
   * @param vec The vector to access
   * @return Reference to the front element
   * @throws std::out_of_range if the vector is empty
   */
  template <typename VecType>
  static auto AccessFront(VecType& vec) -> decltype((vec.front())) {
    if (vec.empty()) throw std::out_of_range("front on empty StrBlob");
    return vec.front();
  }

  /**
   * @brief Template helper for accessing back element
   * @tparam VecType Type of vector (const or non-const)
   * @param vec The vector to access
   * @return Reference to the back element
   * @throws std::out_of_range if the vector is empty
   */
  template <typename VecType>
  static auto AccessBack(VecType& vec) -> decltype((vec.back())) {
    if (vec.empty()) throw std::out_of_range("back on empty StrBlob");
    return vec.back();
  }

  /**
   * @brief Template helper for accessing element at index
   * @tparam VecType Type of vector (const or non-const)
   * @param vec The vector to access
   * @param idx Index of the element to access
   * @return Reference to the requested element
   * @throws std::out_of_range if idx is out of range
   */
  template <typename VecType>
  static auto AccessAt(VecType& vec, SizeType idx) -> decltype((vec.at(idx))) {
    if (idx >= vec.size())
      throw std::out_of_range("index out of range in StrBlob");
    return vec.at(idx);
  }

 private:
  // Shared pointer to the underlying vector of strings
  std::shared_ptr<std::vector<std::string>> data_;
};

#endif  // CHAPTER_12_EXERCISE_02_H_