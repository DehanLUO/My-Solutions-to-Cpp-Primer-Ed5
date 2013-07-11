/*
 * Exercise 16.49: Explain what happens in each of the following calls:
 *     template <typename T> void f(T);
 *     template <typename T> void f(const T*);
 *     template <typename T> void g(T);
 *     template <typename T> void g(T*);
 *     int i = 42, *p = &i;
 *     const int ci = 0, *p2 = &ci;
 *     g(42);   g(p);   g(ci);   g(p2);
 *     f(42);   f(p);   f(ci);   f(p2);
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-16/exercise-49.cc && ./main

 */
