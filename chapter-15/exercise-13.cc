/*
 * Exercise 15.13: Given the following classes, explain each print function:
 *     class base {
 *      public:
 *       string name() { return basename; }
 *       virtual void print(ostream &os) { os << basename; }
 *
 *      private:
 *       string basename;
 *     };
 *     class derived : public base {
 *      public:
 *       void print(ostream &os) {
 *         print(os);
 *         os << " " << i;
 *       }
 *
 *      private:
 *       int i;
 *     };
 * If there is a problem in this code, how would you fix it?
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-15/exercise-13.cc && ./main

 */
