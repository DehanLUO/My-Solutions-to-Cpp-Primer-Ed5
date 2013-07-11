/*
 * Exercise 16.36: What happens in the following calls:
 *     template <typename T> f1(T, T);
 *     template <typename T1, typename T2) f2(T1, T2);
 *     int i = 0, j = 42, *p1 = &i, *p2 = &j;
 *     const int *cp1 = &i, *cp2 = &j;
 *     (a) f1(p1, p2);   (b) f2(p1, p2);  (c) f1(cp1, cp2);
 *     (d) f2(cp1, cp2); (e) f1(p1, cp1); (e) f2(p1, cp1);
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-16/exercise-36.cc && ./main

 */
