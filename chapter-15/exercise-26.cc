/*
 * Exercise 15.26: Define the Quote and Bulk_quote copy-control members to do
 * the same job as the synthesized versions. Give them and the other
 * constructors print statements that identify which function is running. Write
 * programs using these classes and predict what objects will be created and
 * destroyed. Compare your predictions with the output and continue
 * experimenting until your predictions are reliably correct.
 */

#include "exercise-26-bulkquote.h"  // BulkQuote

/**
 * @brief Function demonstrating pass by value (invokes copy constructor)
 * @param item Quote object passed by value
 */
void ProcessQuoteByValue(Quote item) {
  std::cout << "Processing quote by value: " << item.ISBN() << "\n";
}

/**
 * @brief Function demonstrating pass by reference (no copying)
 * @param item Quote reference
 */
void ProcessQuoteByReference(const Quote& item) {
  std::cout << "Processing quote by reference: " << item.ISBN() << "\n";
}

int main() {
  std::cout << "1. DIRECT OBJECT CREATION:\n";
  {
    std::cout << "Creating BulkQuote object...\n";
    BulkQuote bq1("978-1234567890", 50.0, 10, 0.1);
    std::cout << "BulkQuote object created successfully\n\n";
  }
  std::cout << "BulkQuote object destroyed (out of scope)\n\n";

  std::cout << "2. COPY CONSTRUCTION:\n";
  {
    BulkQuote original("978-9876543210", 30.0, 5, 0.15);
    std::cout << "Creating copy...\n";
    BulkQuote copy = original;  // Copy constructor
    std::cout << "Copy created successfully\n\n";
  }
  std::cout << "Original and copy destroyed\n\n";

  std::cout << "3. MOVE CONSTRUCTION:\n";
  {
    BulkQuote temp("978-5555555555", 25.0, 8, 0.2);
    std::cout << "Moving object...\n";
    BulkQuote moved = std::move(temp);  // Move constructor
    std::cout << "Object moved successfully\n\n";
  }
  std::cout << "Moved object destroyed\n\n";

  std::cout << "4. POLYMORPHIC BEHAVIOR:\n";
  {
    BulkQuote derived("978-1111111111", 40.0, 12, 0.25);
    Quote& base_ref = derived;
    std::cout << "Polymorphic reference created\n\n";

    std::cout << "Calling function with pass by value...\n";
    ProcessQuoteByValue(derived);  // Slicing occurs - copies only Quote part
    std::cout << "Function call completed\n\n";

    std::cout << "Calling function with pass by reference...\n";
    ProcessQuoteByReference(
        derived);  // No copying - preserves polymorphic behavior
    std::cout << "Function call completed\n\n";
  }
  std::cout << "Polymorphic objects destroyed\n\n";

  std::cout << "5. CONTAINER USAGE:\n";
  {
    std::vector<BulkQuote> quotes;
    std::cout << "Vector created\n";

    std::cout << "Emplacing object...\n";
    quotes.emplace_back("978-9999999999", 35.0, 6,
                        0.18);  // Direct construction in vector
    std::cout << "Object emplaced\n";

    std::cout << "Pushing back object...\n";
    BulkQuote temp("978-8888888888", 45.0, 15, 0.3);
    quotes.push_back(temp);  // Copy construction in vector
    std::cout << "Object pushed back\n\n";
  }
  std::cout << "Vector and contents destroyed\n\n";

  std::cout << "6. ASSIGNMENT OPERATIONS:\n";
  {
    BulkQuote bq1("978-7777777777", 20.0, 4, 0.12);
    BulkQuote bq2("978-6666666666", 60.0, 20, 0.4);

    std::cout << "Performing copy assignment...\n";
    bq1 = bq2;  // Copy assignment
    std::cout << "Copy assignment completed\n";

    std::cout << "Performing move assignment...\n";
    bq1 = std::move(bq2);  // Move assignment
    std::cout << "Move assignment completed\n\n";
  }
  std::cout << "Assignment test objects destroyed\n\n";

  return 0;
}

/*
 * $ g++ -o main chapter-15/exercise-26.cc && ./main
 * 1. DIRECT OBJECT CREATION:
 * Creating BulkQuote object...
 * Quote(const std::string& 978-1234567890, double 50) called
 * DiscQuote(const std::string& 978-1234567890, double 50, std::size_t 10, double 0.1) called
 * BulkQuote(const std::string& 978-1234567890, double 50, std::size_t 10, double 0.1) called
 * BulkQuote object created successfully
 *
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * BulkQuote object destroyed (out of scope)
 *
 * 2. COPY CONSTRUCTION:
 * Quote(const std::string& 978-9876543210, double 30) called
 * DiscQuote(const std::string& 978-9876543210, double 30, std::size_t 5, double 0.15) called
 * BulkQuote(const std::string& 978-9876543210, double 30, std::size_t 5, double 0.15) called
 * Creating copy...
 * Quote(const Quote& other) called
 * DiscQuote(const DiscQuote& other) called
 * BulkQuote(const BulkQuote& other) called
 * Copy created successfully
 *
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * Original and copy destroyed
 *
 * 3. MOVE CONSTRUCTION:
 * Quote(const std::string& 978-5555555555, double 25) called
 * DiscQuote(const std::string& 978-5555555555, double 25, std::size_t 8, double 0.2) called
 * BulkQuote(const std::string& 978-5555555555, double 25, std::size_t 8, double 0.2) called
 * Moving object...
 * Quote(Quote&& other) called
 * DiscQuote(DiscQuote&& other) called
 * BulkQuote(BulkQuote&& other) called
 * Object moved successfully
 *
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * Moved object destroyed
 *
 * 4. POLYMORPHIC BEHAVIOR:
 * Quote(const std::string& 978-1111111111, double 40) called
 * DiscQuote(const std::string& 978-1111111111, double 40, std::size_t 12, double 0.25) called
 * BulkQuote(const std::string& 978-1111111111, double 40, std::size_t 12, double 0.25) called
 * Polymorphic reference created
 *
 * Calling function with pass by value...
 * Quote(const Quote& other) called
 * Processing quote by value: 978-1111111111
 * ~Quote() called
 * Function call completed
 *
 * Calling function with pass by reference...
 * Processing quote by reference: 978-1111111111
 * Function call completed
 *
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * Polymorphic objects destroyed
 *
 * 5. CONTAINER USAGE:
 * Vector created
 * Emplacing object...
 * Quote(const std::string& 978-9999999999, double 35) called
 * DiscQuote(const std::string& 978-9999999999, double 35, std::size_t 6, double 0.18) called
 * BulkQuote(const std::string& 978-9999999999, double 35, std::size_t 6, double 0.18) called
 * Object emplaced
 * Pushing back object...
 * Quote(const std::string& 978-8888888888, double 45) called
 * DiscQuote(const std::string& 978-8888888888, double 45, std::size_t 15, double 0.3) called
 * BulkQuote(const std::string& 978-8888888888, double 45, std::size_t 15, double 0.3) called
 * Quote(const Quote& other) called
 * DiscQuote(const DiscQuote& other) called
 * BulkQuote(const BulkQuote& other) called
 * Quote(Quote&& other) called
 * DiscQuote(DiscQuote&& other) called
 * BulkQuote(BulkQuote&& other) called
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * Object pushed back
 *
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * Vector and contents destroyed
 *
 * 6. ASSIGNMENT OPERATIONS:
 * Quote(const std::string& 978-7777777777, double 20) called
 * DiscQuote(const std::string& 978-7777777777, double 20, std::size_t 4, double 0.12) called
 * BulkQuote(const std::string& 978-7777777777, double 20, std::size_t 4, double 0.12) called
 * Quote(const std::string& 978-6666666666, double 60) called
 * DiscQuote(const std::string& 978-6666666666, double 60, std::size_t 20, double 0.4) called
 * BulkQuote(const std::string& 978-6666666666, double 60, std::size_t 20, double 0.4) called
 * Performing copy assignment...
 * BulkQuote& operator=(const BulkQuote& other) called
 * DiscQuote& operator=(const DiscQuote& other) called
 * Quote& operator=(const Quote& other) called
 * Copy assignment completed
 * Performing move assignment...
 * BulkQuote& operator=(BulkQuote&& other) called
 * DiscQuote& operator=(DiscQuote&& other) called
 * Quote& operator=(Quote&& other) called
 * Move assignment completed
 *
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * ~BulkQuote() called
 * ~DiscQuote() called
 * ~Quote() called
 * Assignment test objects destroyed
 */
