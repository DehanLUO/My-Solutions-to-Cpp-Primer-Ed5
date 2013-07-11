/*
 * Exercise 16.27: For each labeled statement explain what, if any,
 * instantiations happen. If a template is instantiated, explain why; if not,
 * explain why not.
 *     template <typename T> class Stack {};
 *     void f1(Stack<char>);  // (a)
 *     class Exercise {
 *       Stack<double> &rsd;  // (b)
 *       Stack<int> si;       // (c)
 *     };
 *     int main() {
 *       Stack<char> *sc;                   // (d)
 *       f1(*sc);                           // (e)
 *       int iObj = sizeof(Stack<string>);  // (f)
 *     }
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-16/exercise-27.cc && ./main

 */
