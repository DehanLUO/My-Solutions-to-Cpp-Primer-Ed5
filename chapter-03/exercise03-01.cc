/*
 * Exercise 3.1: Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76)
 * with appropriate using declarations.
 */

#include <iostream>  // std::cout

// exercises from § 1.4.1 (p. 13)
int ExerciseC1E09() {
  using std::cout;

  int num = 50;
  int sum = 0;
  while (num <= 100) {
    sum += num++;
  }

  cout << "The sum from 50 to 100 is " << sum << '\n';

  return 0;
}

int ExerciseC1E10() {
  using std::cout;

  int num = 10;
  while (num >= 0) {
    cout << num-- << " ";
  }

  cout << '\n';

  return 0;
}

int ExerciseC1E11() {
  using std::cin;
  using std::cout;

  cout << "Enter two numbers: \n";
  int num_a = 0;
  int num_b = 0;
  cin >> num_a >> num_b;

  if (num_a > num_b) {
    int temp = num_a;
    num_b = num_a;
    num_a = num_b;
  }

  while (num_a <= num_b) {
    cout << num_a++ << " ";
  }

  return 0;
}

// exercises from § 2.6.2 (p. 76)
using std::string;
struct Sales_data {
  string book_nombre;
  uint16_t units_sold = 0;
  float revenue = 0.0F;

  bool Input() {
    using std::cin;

    float price;
    if (cin >> book_nombre >> units_sold >> price) {
      revenue = units_sold * price;
      return true;
    }

    book_nombre.clear();
    units_sold = 0;
    revenue = 0.0F;
    return false;
  }

  float AvgPrice() const {
    if (units_sold) {
      return revenue / units_sold;
    } else {
      return 0.F;
    }
  }

  void Dump() {
    using std::cout;

    cout << book_nombre << ' '  //
         << units_sold << ' '   //
         << revenue << ' '      //
         << AvgPrice() << '\n';
  }
};

int ExerciseC1E20() {
  using std::cout;

  Sales_data book;

  cout << "Enter sales data: \n";
  while (book.Input()) {
    cout << "isbn units_sold revenue avg_price: ";
    book.Dump();
  }

  return 0;
}

int ExerciseC1E21() {
  using std::cout, std::cerr;

  Sales_data sales_data_a;
  Sales_data sales_data_b;

  cout << "Enter two sales records with the same ISBN:\n";
  sales_data_a.Input();
  sales_data_b.Input();
  if (sales_data_a.book_nombre == sales_data_b.book_nombre) {
    sales_data_a.units_sold += sales_data_b.units_sold;
    sales_data_a.revenue += sales_data_b.revenue;
    cout << "Summary: ISBN, quantity sold, total sales revenue, and "
            "average selling price:\n";
    sales_data_a.Dump();
  } else {
    cerr << "ISBNs do not match\n";
    return -1;
  }

  return 0;
}

int ExerciseC1E22() {
  using std::cout, std::cerr;

  Sales_data total;
  Sales_data sales_data;

  cout << "Enter some sales records with the same ISBN:\n";
  if (!total.Input()) {
    cerr << "Invalid data!\n";
    return -1;
  }

  while (sales_data.Input()) {
    if (sales_data.book_nombre == total.book_nombre) {  // same ISBN
      total.units_sold += sales_data.units_sold;
      total.revenue += sales_data.revenue;
    } else {  // different ISBN
      cerr << "ISBNs do not match\n";
      return -1;
    }
  }

  cout << "Summary: ISBN, quantity sold, total sales revenue, and "
          "average selling price:\n";
  total.Dump();

  return 0;
}

int ExerciseC1E23AndC1E24() {
  using std::cerr, std::cout;

  Sales_data sales_base;  // Holds the current ISBN group to compare against

  cout << "Enter some sales records:\n";
  // Read first record as the base case
  if (sales_base.Input()) {
    Sales_data current_sales_record;  // Reads each incoming transaction
    int count = 1;  // Tracks number of records in current ISBN group

    // Process subsequent records
    while (current_sales_record.Input()) {
      if (sales_base.book_nombre == current_sales_record.book_nombre) {
        ++count;  // Increment if same ISBN as base
      } else {
        // Output stats for previous ISBN group
        cout << sales_base.book_nombre << " has " << count
             << " sales records\n";
        sales_base = current_sales_record;  // Start new ISBN group
        count = 1;                          // Reset counter
      }
    }
    // Output the last ISBN group
    cout << sales_base.book_nombre << " has " << count << " sales records\n";
  } else {
    cerr << "No sales records\n";  // Handle empty input case
    return -1;
  }
  return 0;
}

int ExerciseC1E25() {
  using std::cerr, std::endl;

  Sales_data total;  // variable to hold data for the next transaction
  // read the first transaction and ensure that there are data to process
  if (total.Input()) {
    Sales_data trans;  // variable to hold the running sum;

    // read and process the remaining transactions
    while (trans.Input()) {
      // if we are still processing the same book
      if (total.book_nombre == trans.book_nombre) {
        // update the running total
        total.units_sold += trans.units_sold;
        total.revenue += trans.revenue;
      } else {
        // print results for the previous book
        total.Dump();
        total = trans;  // total now refers to the next book
      }
    }
    total.Dump();  // print the last transaction
  } else {
    // no input! warn the user
    cerr << "No data?!" << endl;
    return -1;  // indicate failure
  }
  return 0;
}

int main() {
  ExerciseC1E09();

  ExerciseC1E10();

  ExerciseC1E11();

  ExerciseC1E20();

  ExerciseC1E21();

  ExerciseC1E22();

  ExerciseC1E23AndC1E24();

  ExerciseC1E25();

  return 0;
}
