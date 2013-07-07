/*
 * Exercise 13.4: Assuming Point is a class type with a public copy constructor,
 * identify each use of the copy constructor in this program fragment:
 *     Point global;
 *     Point foo_bar(Point arg) {
 *       Point local = arg, *heap = new Point(global);
 *       *heap = local;
 *       Point pa[4] = {local, *heap};
 *       return *heap;
 *     }
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-13/exercise-04.cc && ./main

 */
