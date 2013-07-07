/*
 * Exercise 12.25: Given the following new expression, how would you delete pa?
 *     int *pa = new int[10];
 */

#include <iostream>  // std::cout, std::ostream

/**
 * @brief Generates a unique, monotonically increasing identifier
 *        for each instance of the Tracked class.
 * @return uint16_t A unique identifier assigned at construction time
 * @note The counter wraps around after 65535 (uint16_t limit)
 * @warning This function is not thread-safe
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
uint16_t GenerateTrackedIndex() {
  static uint16_t count = 0;  // Persistent across function calls
  return count++;
}

class Tracked {
  // Allows access to private data for stream printing
  friend std::ostream& operator<<(std::ostream&, const Tracked&);

 public:
  /**
   * @brief Constructs a Tracked object and assigns a unique identifier.
   *        Logs the construction event to the standard output stream.
   * Time Complexity: O(1)
   * Space Complexity: O(1)
   */
  Tracked();

  /**
   * @brief Destructor for Tracked.
   *        Logs the destruction event to the standard output stream.
   * Time Complexity: O(1)
   * Space Complexity: O(1)
   */
  ~Tracked();

 private:
  uint16_t count_;  // Object-specific unique identifier
};

Tracked::Tracked() : count_(GenerateTrackedIndex()) {
  std::cout << "  CONSTRUCT Tracked @" << this << " | count: " << count_
            << '\n';
}

Tracked::~Tracked() {
  std::cout << "  DESTRUCT Tracked @" << this << " | count: " << count_ << '\n';
}

/**
 * @brief Stream insertion operator overload for displaying Tracked metadata.
 * @param out Reference to the output stream
 * @param tracked Constant reference to a Tracked object
 * @return std::ostream& Reference to the output stream for chaining
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
std::ostream& operator<<(std::ostream& out, const Tracked& tracked) {
  return out << "@" << &tracked << " | count: " << tracked.count_;
}

int main() {
  /*
   * 10 instances of the Tracked class were dynamically allocated using the
   * new[] operator. Each object receives a unique index via
   * GenerateTrackedIndex(), and the Tracked constructor logs the memory address
   * and associated index. The construction occurs in increasing order (from
   * index 0 to 9), reflecting left-to-right memory layout as per the arry model
   * in c++;
   * Output:
   *   CONSTRUCT Tracked @0x6000025211a8 | count: 0
   *   CONSTRUCT Tracked @0x6000025211aa | count: 1
   *   CONSTRUCT Tracked @0x6000025211ac | count: 2
   *   CONSTRUCT Tracked @0x6000025211ae | count: 3
   *   CONSTRUCT Tracked @0x6000025211b0 | count: 4
   *   CONSTRUCT Tracked @0x6000025211b2 | count: 5
   *   CONSTRUCT Tracked @0x6000025211b4 | count: 6
   *   CONSTRUCT Tracked @0x6000025211b6 | count: 7
   *   CONSTRUCT Tracked @0x6000025211b8 | count: 8
   *   CONSTRUCT Tracked @0x6000025211ba | count: 9
   */
  Tracked* pa = new Tracked[10];  // Allocate and construct 10 Tracked objects

  std::cout << *pa << '\n';  // Print first object metadata

  /*
   * When using new[] to allocate an array of objects, the runtime keeps
   * metadata (typically hidden) to track the number of elements. Upon delete[],
   * it destroys the objects in the reverse order of construction to properly
   * clean up dependencies in complex object graphs.
   * Output:
   *   DESTRUCT Tracked @0x6000025211ba | count: 9
   *   DESTRUCT Tracked @0x6000025211b8 | count: 8
   *   DESTRUCT Tracked @0x6000025211b6 | count: 7
   *   DESTRUCT Tracked @0x6000025211b4 | count: 6
   *   DESTRUCT Tracked @0x6000025211b2 | count: 5
   *   DESTRUCT Tracked @0x6000025211b0 | count: 4
   *   DESTRUCT Tracked @0x6000025211ae | count: 3
   *   DESTRUCT Tracked @0x6000025211ac | count: 2
   *   DESTRUCT Tracked @0x6000025211aa | count: 1
   *   DESTRUCT Tracked @0x6000025211a8 | count: 0
   */
  delete[] pa;  // Destruct all objects in array

  /*
   * Even though the program still prints a valid-looking address and value,
   * this is not reliable.
   * Output:
   * @0x6000025211a8 | count: 2043
   * is evidence of use-after-free. The object was already destroyed(count: 0
   * was destructed earlier), so accessing its internal memory results in
   * undefined behaviour. The printed "count: 2043" is garbage memory---an
   * artefact of deallocated memory being reinterpreted as valid content.
   * - Memory may have been reused or marked invalid by the runtime
   * - Results are non-deterministic and may differ across runs, compilers, or
   *   platforms.
   * - Future dereferences may cause segmentation faults or corrupt program
   *   state.
   */
  std::cout << *pa << '\n';  // Dangling pointer dereference (ub)

  /*
   * Assigning nullptr to a pointer after deletion is widely regarded as best
   * practie:
   * - Semantic clarity: Indicates ownership has been released and pointer is
   *   invalidated.
   * - Prevents accidental re-use: Dereferencing a nullptr causes a consistent
   *   and immediate crash (e.g., segmnentation fault), which is easier to debug
   *   than silent memory corruption.
   * - Enables safe conditional logic:
   *     if(pa) { ... } // Skips execution when pointer is null
   */
  pa = nullptr;  // Clear pointer to avoid accidental use

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-25-details.cc && ./main
 *   CONSTRUCT Tracked @0x6000025211a8 | count: 0
 *   CONSTRUCT Tracked @0x6000025211aa | count: 1
 *   CONSTRUCT Tracked @0x6000025211ac | count: 2
 *   CONSTRUCT Tracked @0x6000025211ae | count: 3
 *   CONSTRUCT Tracked @0x6000025211b0 | count: 4
 *   CONSTRUCT Tracked @0x6000025211b2 | count: 5
 *   CONSTRUCT Tracked @0x6000025211b4 | count: 6
 *   CONSTRUCT Tracked @0x6000025211b6 | count: 7
 *   CONSTRUCT Tracked @0x6000025211b8 | count: 8
 *   CONSTRUCT Tracked @0x6000025211ba | count: 9
 * @0x6000025211a8 | count: 0
 *   DESTRUCT Tracked @0x6000025211ba | count: 9
 *   DESTRUCT Tracked @0x6000025211b8 | count: 8
 *   DESTRUCT Tracked @0x6000025211b6 | count: 7
 *   DESTRUCT Tracked @0x6000025211b4 | count: 6
 *   DESTRUCT Tracked @0x6000025211b2 | count: 5
 *   DESTRUCT Tracked @0x6000025211b0 | count: 4
 *   DESTRUCT Tracked @0x6000025211ae | count: 3
 *   DESTRUCT Tracked @0x6000025211ac | count: 2
 *   DESTRUCT Tracked @0x6000025211aa | count: 1
 *   DESTRUCT Tracked @0x6000025211a8 | count: 0
 * @0x6000025211a8 | count: 2043
 */
