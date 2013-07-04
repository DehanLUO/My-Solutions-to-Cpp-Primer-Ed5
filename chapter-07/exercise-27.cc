/*
 * Exercise 7.27: Add the move, set, and display operations to your version of
 * Screen. Test your class by executing the following code:
 *     Screen myScreen(5, 5, 'X');
 *     myScreen.move(4,0).set('#').display(cout);
 *     cout << "\n";
 *     myScreen.display(cout);
 *     cout << "\n";
 */

#include "exercise-27.h"  // Screen

#include <iostream>  // std::cout

int main() {
  Screen my_screen(5, 5, 'X');
  my_screen.Move(4, 0).Set('#').Display(std::cout);
  std::cout << "\n";
  my_screen.Display(std::cout);
  std::cout << "\n";
}

/* $ g++ -o main chapter-07/exercise-27.cc && ./main
 * XXXXXX
 * XXXXXX
 * XXXXXX
 * XXXXXX
 * #XXXXX
 * XXXXXX
 *
 * XXXXXX
 * XXXXXX
 * XXXXXX
 * XXXXXX
 * #XXXXX
 * XXXXXX
 *
 */
