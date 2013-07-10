/*
 * Exercise 14.32: Define a class that holds a pointer to a StrBlobPtr. Define
 * the overloaded arrow operator for that class.
 */

#ifndef CHAPTER_14_EXERCISE_32_H_
#define CHAPTER_14_EXERCISE_32_H_

#include "exercise-30-strblob.h"  // StrBlobPtr

class StrBlobPtrPointer {
 public:
  /**
   * @brief Default constructor
   * @post Creates a null pointer wrapper
   */
  StrBlobPtrPointer() noexcept : ptr_(nullptr) {}

  /**
   * @brief Construct from existing StrBlobPtr pointer (non-owning)
   * @param ptr Pointer to StrBlobPtr to wrap
   * @post Non-owning reference to existing object
   */
  explicit StrBlobPtrPointer(StrBlobPtr& p) : ptr_(&p) {}

  std::string* operator->() const {
    if (nullptr == ptr_)
      throw std::logic_error("Dereference of null StrBlobPtrPointer");

    return ptr_->operator->();
  }

 private:
  StrBlobPtr* ptr_;
};

#endif  // CHAPTER_14_EXERCISE_32_H_
