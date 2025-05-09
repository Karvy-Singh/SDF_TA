#include "classes.hpp"
#include "exceptions.hpp"
#include <ctime>
#include <iostream>

int main() {
  // Create library instance
  Library lib("Community Library", "Sec-62 Noida");

  // Add books
  Book b1("B101", "A Song of Ice and Fire", "George RR Martin", 2013);
  Book b2("B102", "Pet Sematary", "Stephen King", 2008);
  Book b3("B103", "Goosebumps", "R.L. Stine", 2014);

  lib.addBook(b1);
  lib.addBook(b2);
  lib.addBook(b3);

  // Register members
  Member m1("M001", "Karvy", "karvy@gmail.com", "1234567890");
  Member m2("M002", "Harsh", "harsh@gmail.com", "0987654321");
  Member m3("M003", "Rudra", "rudra@gmail.com", "4567890123");

  lib.registerMember(m1);
  lib.registerMember(m2);
  lib.registerMember(m3);

  // Issue book to member
  std::cout << "\nIssuing book B101 to M001...\n";
  lib.issueBook("M001", "B101");

  // Issue another book
  std::cout << "\nIssuing book B102 to M002...\n";
  lib.issueBook("M002", "B102");

  // Return book (simulate 8 days late)
  std::time_t now = std::time(nullptr);
  std::time_t lateReturn = now + 8 * 24 * 60 * 60; // 8 days after issue

  std::cout << "\nReturning book B101 from M001...\n";
  lib.returnBook("M001", "B101", lateReturn);

  // Calculate fine (assumes latest return txn is for B101)
  std::string latestTxnID = "TXN_B101_M001";
  std::cout << "Calculating fine for transaction " << latestTxnID << "...\n";
  double fine = lib.calculateFine(latestTxnID, lateReturn);
  std::cout << "Fine: ₹" << fine << "\n";

  // Generate report
  std::cout << "\nGenerating full report...\n";
  lib.generateReport();

  return 0;
}

// EXCEPTIONS

// int main() {
//     // 1) Set up library, books, and a single member
//     Library lib("Community Library", "Sec-62 Noida");
//
//     // Add two books
//   Book b1("B101", "A Song of Ice and Fire", "George RR Martin", 2013);
//   Book b2("B102", "Pet Sematary", "Stephen King", 2008);
//     // Register one member
//     lib.registerMember(Member("M001", "Saatwik", "saatwik@mail.com",
//     "555-1234"));
//
//     std::cout << " Case 1: Invalid Member ID \n";
//     try {
//         // nested try to demonstrate re-throw
//         try {
//             lib.issueBook("M999", "B101");
//         }
//         catch (const InvalidMemberIDException& ex) {
//             std::cerr << ex.what() << "\n";
//             throw;  // rethrow to outer handler
//         }
//     }
//     catch (const LibraryException& ex) {
//         std::cerr << "Library-level catch: " << ex.what() << "\n\n";
//     }
//
//     std::cout << "Case 2: Book Not Available \n";
//     try {
//         // asking for a non-existent book
//         lib.issueBook("M001", "B999");
//     }
//     catch (const BookNotAvailableException& ex) {
//         std::cerr << ex.what() << "\n\n";
//     }
//     catch (const LibraryException& ex) {
//         // fallback for any other library exception
//         std::cerr << ex.what() << "\n\n";
//     }
//
//     std::cout << "Case 3: Maximum Issue Limit\n";
//     try {
//         // suppose MAX_ISSUES is 2, so first two succeed, third throws
//         lib.issueBook("M001", "B101");
//         lib.issueBook("M001", "B102");
//         lib.issueBook("M001", "B103");
//         lib.issueBook("M001", "B104");
//     }
//     catch (const IssueLimitExceededException& ex) {
//         std::cerr << ex.what() << "\n\n";
//     }
//     catch (const LibraryException& ex) {
//         std::cerr << ex.what() << "\n\n";
//     }
//
//     return 0;
// }
//
