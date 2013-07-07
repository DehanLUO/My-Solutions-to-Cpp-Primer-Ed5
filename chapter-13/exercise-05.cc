/*
 * Exercise 13.5: Given the following sketch of a class, write a copy
 * constructor that copies all the members. Your constructor should dynamically
 * allocate a new string (§ 12.1.2, p. 458) and copy the object to which ps
 * points, rather than copying ps itself.
 *     class HasPtr {
 *      public:
 *       HasPtr(const std::string &s = std::string()) :
 *           ps(new std::string(s)), i(0) {}
 *      private:
 *       std::string *ps;
 *       int i;
 *     };
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-13/exercise-05.cc && ./main

 */
