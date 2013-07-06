/*
 * Exercise 11.2: Give an example of when each of list, vector, deque, map, and
 * set might be most useful.
 */

#include <deque>     // std::deque
#include <iostream>  // std::cout
#include <list>      // std::list
#include <map>       // std::map
#include <set>       // std::set
#include <vector>    // std::vector

int main() {
  /*
   * 1. std::vector:
   *    - Use case: Dynamic array needing random access
   *    - Example: Storing game high scores
   *    - Why: Fast access by index, memory efficient
   */
  std::vector<int> high_scores = {95, 88, 100, 76};
  std::cout << "Third high score: " << high_scores[2] << '\n';

  /*
   * 2. std::list:
   *    - Use case: Frequent insertions/deletions in middle
   *    - Example: Music playlist with frequent reordering
   *    - Why: O(1) insert/delete anywhere
   */
  std::list<std::string> playlist = {"Song A", "Song B", "Song C"};
  playlist.insert(std::next(playlist.begin()), "New Song");

  /*
   * 3. std::deque:
   *    - Use case: Queue with growth at both ends
   *    - Example: Sliding window of recent network packets
   *    - Why: Fast push/pop at both ends
   */
  std::deque<std::string> packet_window;
  packet_window.push_back("Packet1");
  packet_window.push_front("Packet0");

  /*
   * 4. std::map:
   *    - Use case: Key-value lookups with ordering
   *    - Example: Dictionary (word -> definition)
   *    - Why: Fast O(log n) lookup, sorted keys
   */
  std::map<std::string, std::string> dictionary = {
      {"apple", "A fruit"}, {"banana", "Yellow curved fruit"}};
  std::cout << "Definition of apple: " << dictionary["apple"] << '\n';

  /*
   * 5. std::set:
   *    - Use case: Unique collection with fast lookup
   *    - Example: User whitelist
   *    - Why: Automatic deduplication, sorted order
   */
  std::set<std::string> whitelist = {"user1", "user2", "user3"};
  if (whitelist.count("user2")) {
    std::cout << "User2 is authorized\n";
  }

  return 0;
}

/*
 * $ g++ -o main chapter-11/exercise-02.cc && ./main
 * Third high score: 100
 * Definition of apple: A fruit
 * User2 is authorized
 */
