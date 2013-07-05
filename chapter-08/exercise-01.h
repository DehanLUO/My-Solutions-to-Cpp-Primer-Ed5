/*
 * Exercise 8.1: Write a function that takes and returns an istream&. The
 * function should read the stream until it hits end-of-file. The function
 * should print what it reads to the standard output. Reset the stream so that
 * it is valid before returning the stream.
 */

#ifndef CHAPTER_08_EXERCISE_01_H_
#define CHAPTER_08_EXERCISE_01_H_

#include <iomanip>   // std::quoted
#include <iostream>  // std::istream, std::cin, std::cout
#include <string>    // std::string

/**
 * @brief RAII guard for complete stream state preservation
 *
 * Captures and restores:
 * - Stream state flags
 */
class StreamStateGuard {
 public:
  explicit StreamStateGuard(std::istream& istream)
      : istream_(istream), original_iostate_(istream.rdstate()) {}

  ~StreamStateGuard() { istream_.clear(original_iostate_); }

 private:
  std::istream& istream_;
  std::ios::iostate original_iostate_;
};

/**
 * @brief Processes input stream until EOF with type-safe extraction
 * @tparam T Type to extract from stream
 * @param istream Input stream to process
 * @param ostream Output stream for results
 * @return Reference to the restored input stream
 *
 * Features:
 * - Preserves all stream state
 * - Handles extraction failures robustly
 * - Configurable output stream
 * - Proper whitespace handling
 */
template <typename T>
std::istream& ProcessInputStream(std::istream& istream,
                                 std::ostream& ostream = std::cout) {
  StreamStateGuard rdstate_guard(istream);

  while (!istream.eof()) {
    T value;

    if (istream >> value) {
      ostream << value << ' ';
      continue;
    }

    istream.fail();
    istream.clear();

    std::string junk;
    istream >> junk;
    ostream << "[Illegal input: " << std::quoted(junk) << "]\n";
  }

  return istream;
}

#endif  // CHAPTER_08_EXERCISE_01_H_