/*
 * Exercise 16.11: The following definition of List is incorrect. How would you
 * fix it?
 *     template <typename elemType>
 *     class ListItem;
 *     template <typename elemType>
 *     class List {
 *      public:
 *       List<elemType>();
 *       List<elemType>(const List<elemType> &);
 *       List<elemType> &operator=(const List<elemType> &);
 *       ~List();
 *       void insert(ListItem *ptr, elemType value);
 *
 *      private:
 *       ListItem *front, *end;
 *     };
 */

int main() { return 0; }

/*
 * $ g++ -o main chapter-16/exercise-11.cc && ./main

 */
