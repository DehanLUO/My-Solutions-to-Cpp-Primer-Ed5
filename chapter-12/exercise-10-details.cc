#include <iostream>  // std::cout
#include <memory>    // std::shared_ptr

/**
 * @brief A diagnostic class tracking object lifecycle events
 *
 * Provides instrumentation for construction, copying, moving, and destruction
 * with memory address visibility for precise object tracking.
 */
struct Tracked {
  Tracked() { std::cout << "  CONSTRUCT Tracked @" << this << "\n"; }

  Tracked(const Tracked&) {
    std::cout << "  COPY-CONSTRUCT Tracked @" << this << "\n";
  }

  Tracked(Tracked&&) noexcept {
    std::cout << "  MOVE-CONSTRUCT Tracked @" << this << "\n";
  }

  ~Tracked() { std::cout << "  DESTROY Tracked @" << this << "\n"; }
};

/**
 * @brief Instrumented shared_ptr wrapper demonstrating ownership semantics
 *
 * Extends std::shared_ptr with diagnostic output for:
 * - Construction/destruction sequencing
 * - Reference count transitions
 * - Pointer state changes
 */
struct InstrumentedShared : public std::shared_ptr<Tracked> {
  using std::shared_ptr<Tracked>::shared_ptr;

  // Conversion constructor
  InstrumentedShared(shared_ptr& p) : shared_ptr(p) {
    std::cout << "    CONSTRUCT IS @" << this << " | Managing @" << get()
              << " | Refcount: " << use_count() << "\n";
  }

  // Copy constructor
  InstrumentedShared(const InstrumentedShared& other) : shared_ptr(other) {
    std::cout << "    COPY IS @" << this << " | Managing @" << get()
              << " | Refcount: " << use_count() << "\n";
  }

  // Move constructor
  InstrumentedShared(InstrumentedShared&& other) noexcept
      : shared_ptr(std::move(other)) {
    std::cout << "    MOVE IS @" << this << " | Managing @" << get()
              << " | Refcount: " << use_count() << "\n";
  }

  ~InstrumentedShared() {
    std::cout << "    DESTROY IS @" << this;
    if (get()) {
      std::cout << " | Managing @" << get() << " | Refcount: " << use_count();
    } else {
      std::cout << " | Null state";
    }
    std::cout << "\n";
  }

  void Report() const {
    std::cout << "    CURRENT STATE @" << this;
    if (get()) {
      std::cout << " | Managing @" << get() << " | Refcount: " << use_count();
    } else {
      std::cout << " | Null state";
    }
    std::cout << "\n";
  }
};

/**
 * @brief Demonstrates shared ownership semantics
 * @param is Shared pointer instance passed by value
 *
 * Shows reference count behavior during function:
 * - Entry (parameter construction)
 * - Scope lifetime
 * - Exit (parameter destruction)
 */
void DemonstrateOwnership(InstrumentedShared is) {
  std::cout << "  ENTER DemonstrateOwnership()\n";
  is.Report();
  std::cout << "  EXIT DemonstrateOwnership()\n";
}

int main() {
  std::cout << "=== BEGIN ANALYSIS ===\n";

  /*
   * Baseline object construction
   * Output:
   *   CONSTRUCT Tracked @0x7ff7bcd73c2b
   */
  Tracked origin;

  // Shared pointer initialization
  std::cout << "Creating shared_ptr<Tracked>(copy from origin)\n";
  /*
   * Constructs a `Tracked` object via copy-construction from `origin`,
   * since `make_shared` requires a concrete instance to initialize the shared
   * object.
   * Output:
   *   COPY-CONSTRUCT Tracked @0x6000012dd1b8
   */
  auto base_ptr = std::make_shared<Tracked>(origin);

  // Instrumented wrapper construction
  std::cout << "\nConstructing InstrumentedShared primary(base_ptr)\n";
  /*
   * Constructs a `MyShared` object from an existing `shared_ptr<Tracked>`. This
   * invokes the base class copy constructor (`shared_ptr`), increasing the
   * reference count to 2 (base_ptr + primary).
   * Output:
   *     CONSTRUCT IS @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
   */
  InstrumentedShared primary(base_ptr);
  /*
   * Displays the internal state of `primary`:
   *     CURRENT STATE @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
   */
  primary.Report();

  std::cout << "\nTEST CASE 1: Direct pass-by-value\n";
  /*
   * `primary` is passed to `process()` by value, which invokes the copy
   * constructor of `InstrumentedShared`. This leads to a new
   * `InstrumentedShared` instance with the same underlying pointer,
   * incrementing use_count to 3 (base_ptr + primary + is).
   * Output:
   *     COPY IS @0x7ff7bcd73bd8 | Managing @0x6000012dd1b8 | Refcount: 3
   *
   * When `process()` returns, the copied `InstrumentedShared` instance goes out
   * of scope and is destructed.
   * Output:
   *     DESTROY IS @0x7ff7bcd73bd8 | Managing @0x6000012dd1b8 | Refcount: 3
   * Although the reference count decreases from 3 to 2, the destructor output
   * still shows use_count = 3 because the reference count has not yet been
   * decremented at the time of printing.
   */
  DemonstrateOwnership(primary);
  /*
   * Verifies that the reference count is back to 2 after `process()` completes.
   *     CURRENT STATE @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
   */
  primary.Report();

  // Temporary construction demonstration
  std::cout << "\nTEST CASE 2: Temporary construction\n";
  /*
   * Step 1:
   * Constructs a temporary `InstrumentedShared` object via copy constructor
   * from `primary` (since `a` is an lvalue). This increases use_count to 3
   * (base_ptr + primary + temporary).
   * Output:
   *     COPY IS @0x7ff7bcd73bb8 | Managing @0x6000012dd1b8 | Refcount: 3
   *
   * Step 2: The temporary `InstrumentedShared` is passed to `process()` by
   * rvalue, which triggers the move constructor. Ownership is transferred to
   * the function parameter. As a result, the temporary's internal pointer
   * becomes `nullptr`, but use_count remains 3 (base_ptr + primary + is).
   * Output:
   *     MOVE IS @0x7ff7bcd73bc8 | Managing @0x6000012dd1b8 | Refcount: 3
   *
   * Step 3:
   * Inside `process()`, the moved-to object still manages the resource and
   * prints use_count = 3 (base_ptr + primary + is).
   * Output:
   *   ENTER DemonstrateOwnership()
   *     CURRENT STATE @0x7ff7bcd73bc8 | Managing @0x6000012dd1b8 | Refcount: 3
   *   EXIT DemonstrateOwnership()
   *
   * Step 4:
   * On function return:
   * - The moved-to parameter is destructed first: use_count = 3 → 2.
   *   (Destructor output still shows use_count = 3 before decrement.)
   * - The original temporary (moved-from) object is destructed next, but since
   * its pointer is null, it does not affect the reference count.
   * Output:
   *     DESTROY IS @0x7ff7bcd73bc8 | Managing @0x6000012dd1b8 | Refcount: 3
   *     DESTROY IS @0x7ff7bcd73bb8 | Null state
   */
  DemonstrateOwnership(InstrumentedShared(primary));
  /*
   * Verifies that the reference count is back to 2 after `process()` completes.
   *     CURRENT STATE @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
   */
  primary.Report();

  std::cout << "=== END ANALYSIS ===\n";
  return 0;
}

/*
 * g++ -std=c++11 -O0 -fno-elide-constructors -o main chapter-12/exercise-10-details.cc && ./main
 * === BEGIN ANALYSIS ===
 *   CONSTRUCT Tracked @0x7ff7bcd73c2b
 * Creating shared_ptr<Tracked>(copy from origin)
 *   COPY-CONSTRUCT Tracked @0x6000012dd1b8
 *
 * Constructing InstrumentedShared primary(base_ptr)
 *     CONSTRUCT IS @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
 *     CURRENT STATE @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
 *
 * TEST CASE 1: Direct pass-by-value
 *     COPY IS @0x7ff7bcd73bd8 | Managing @0x6000012dd1b8 | Refcount: 3
 *   ENTER DemonstrateOwnership()
 *     CURRENT STATE @0x7ff7bcd73bd8 | Managing @0x6000012dd1b8 | Refcount: 3
 *   EXIT DemonstrateOwnership()
 *     DESTROY IS @0x7ff7bcd73bd8 | Managing @0x6000012dd1b8 | Refcount: 3
 *     CURRENT STATE @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
 *
 * TEST CASE 2: Temporary construction
 *     COPY IS @0x7ff7bcd73bb8 | Managing @0x6000012dd1b8 | Refcount: 3
 *     MOVE IS @0x7ff7bcd73bc8 | Managing @0x6000012dd1b8 | Refcount: 3
 *   ENTER DemonstrateOwnership()
 *     CURRENT STATE @0x7ff7bcd73bc8 | Managing @0x6000012dd1b8 | Refcount: 3
 *   EXIT DemonstrateOwnership()
 *     DESTROY IS @0x7ff7bcd73bc8 | Managing @0x6000012dd1b8 | Refcount: 3
 *     DESTROY IS @0x7ff7bcd73bb8 | Null state
 *     CURRENT STATE @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
 * === END ANALYSIS ===
 *     DESTROY IS @0x7ff7bcd73be8 | Managing @0x6000012dd1b8 | Refcount: 2
 *   DESTROY Tracked @0x6000012dd1b8
 *   DESTROY Tracked @0x7ff7bcd73c2b
 */
