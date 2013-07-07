/*
 * Exercise 13.14: Assume that numbered is a class with a default constructor
 * that generates a unique serial number for each object, which is stored in a
 * data member named mysn. Assuming numbered uses the synthesized copy-control
 * members and given the following function:
 *     void f(numbered s) { cout << s.mysn << endl; }
 * what output does the following code produce?
 *     numbered a, b = a, c = b;
 *     f(a); f(b); f(c);
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-13/exercise-14.cc && ./main

 */
