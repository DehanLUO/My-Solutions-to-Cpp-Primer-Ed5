
// Exercise 2.39: Compile the following program to see what happens when you
// forget the semicolon after a class definition. Remember the message for
// future reference.
//     struct Foo { /* empty */ } // Note: no semicolon
//     int main() {
//       return 0;
//     }

struct Foo { /* empty */
}  // Note: no semicolon

int main() {
  return 0;
}

// $ g++ -o main exercise-39.cc && ./main
// exercise-39.cc:10:27: error: expected ';' after struct
//    10 | struct Foo { /* empty */ }  // Note: no semicolon
//       |                           ^
//       |                           ;
// 1 error generated.