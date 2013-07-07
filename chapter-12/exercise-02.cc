/*
 * Exercise 12.2: Write your own version of the StrBlob class including the
 * const versions of front and back.
 */

#include "exercise-02.h"  // StrBlob

#include <iostream>  //  std::cout

int main() {
  // Create and populate a StrBlob
  StrBlob blob{"apple", "banana", "cherry"};

  // Access elements
  std::cout << "Front: " << blob.Front() << '\n';
  std::cout << "Back: " << blob.Back() << '\n';

  // Modify elements
  blob.Front() = "avocado";
  blob.At(2) = "grape";
  blob.PushBack("orange");

  // Const access
  const StrBlob const_blob = blob;
  std::cout << "Const front: " << const_blob.Front() << '\n';
  std::cout << "Const At(2): " << const_blob.At(2) << '\n';
  std::cout << "Const back: " << const_blob.Back() << '\n';

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-02.cc && ./main
 * Front: apple
 * Back: cherry
 * Const front: avocado
 * Const At(2): grape
 * Const back: orange
 */
