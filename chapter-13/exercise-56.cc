/*
 * Exercise 13.56: What would happen if we defined sorted as:
 *     Foo Foo::sorted() const& {
 *       Foo ret(*this);
 *       return ret.sorted();
 *     }
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-13/exercise-56.cc && ./main

 */
