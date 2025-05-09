#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "linkedlist.hpp"
#include <ctime>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

class Book {
private:
  string bookID;
  string title;
  string author;
  int publicationYear;
  bool isAvailable;

public:
  // Constructors
  Book() : publicationYear(0), isAvailable(true) {}
  Book(string id, string t, string a, int year, bool available = true)
      : bookID(id), title(t), author(a), publicationYear(year),
        isAvailable(available) {}

  // Getters
  string getID() const { return bookID; }
  string getTitle() const { return title; }
  string getAuthor() const { return author; }
  int getPublicationYear() const { return publicationYear; }
  bool getAvailability() const { return isAvailable; }

  // Setters
  void setAvailability(bool available) { isAvailable = available; }

  // Display details
  void printDetails() const {
    cout << "Book ID: " << bookID << "\nTitle: " << title
         << "\nAuthor: " << author << "\nYear: " << publicationYear
         << "\nStatus: " << (isAvailable ? "Available" : "Not Available")
         << "\n";
  }

  // Operator overload for printing in list
  friend ostream &operator<<(ostream &os, const Book &book) {
    os << "[" << book.bookID << "] " << book.title;
    return os;
  }

  // Equality (for search/comparison by ID)
  bool operator==(const Book &other) const { return bookID == other.bookID; }

  bool operator!=(const Book &other) const { return !(*this == other); }
};

class Member {
private:
  string memberID;
  string name;
  string email;
  string phone;

  linkedlist<Book> borrowedBooks;

public:
  // Constructors
  Member() = default;

  Member(const string &id, const string &nm, const string &em, const string &ph)
      : memberID(id), name(nm), email(em), phone(ph) {}

  // Getters
  string getID() const { return memberID; }
  string getName() const { return name; }

  // Register
  void registerMember() const {
    cout << "Member registered: " << name << " [" << memberID << "]\n";
  }

  // Borrow book (adds to borrowedBooks list)
  void borrowBook(const Book &book) {
    if (book.getAvailability()) {
      borrowedBooks.addback(book);
      cout << "Book borrowed: " << book.getTitle() << " by " << name << "\n";
    } else {
      cout << "Book is not available.\n";
    }
  }

  // Return book (removes from borrowedBooks list)
  void returnBook(const std::string &bookID) {
    Book *b = genericSearch<Book, std::string>(
        borrowedBooks, bookID, [](const Book &book, const std::string &id) {
          return book.getID() == id;
        });

    if (b) {
      cout << "Book returned: " << b->getTitle() << "\n";
      borrowedBooks.deletebegin(*b);
    } else {
      std::cout << "Book not found in borrowed list.\n";
    }
  }

  // Display borrowed books
  void printBorrowedBooks() {
    std::cout << "Borrowed books by " << name << ":\n";
    borrowedBooks.printfrwd();
  }

  // Output stream
  friend ostream &operator<<(ostream &os, const Member &m) {
    os << "[" << m.memberID << "] " << m.name;
    return os;
  }
};

class Librarian {
private:
  string employeeID;
  int staffLevel;

public:
  // Constructor
  Librarian(const string &id, int level) : employeeID(id), staffLevel(level) {}

  // Add book to the library's book list
  void addBook(linkedlist<Book> &bookList, const Book &newBook) {
    bookList.addback(newBook);
    cout << "Book added by Librarian " << employeeID << ": "
         << newBook.getTitle() << "\n";
  }

  // Remove a book by ID
  void removeBook(linkedlist<Book> &bookList, const string &bookID) {
    Book *b = genericSearch<Book, string>(
        bookList, bookID,
        [](const Book &b, const string &id) { return b.getID() == id; });

    if (b) {
      bookList.deletebegin(*b);
      cout << "Book removed: " << b->getTitle() << "\n";
    } else {
      cout << "Book not found.\n";
    }
  }

  // Manage a member
  void manageMember(const Member &member) {
    cout << "Managing Member: " << member.getID() << " - " << member.getName()
         << "\n";
  }
};

enum class TransactionType { ISSUE, RETURN };

class Transaction {
private:
  string transactionID;
  string bookID;
  string memberID;
  time_t date; // from ctime``
  TransactionType type;
  time_t dueDate;

public:
  // Constructr
  Transaction(string tid, string bid, string mid, TransactionType t, time_t d,
              std::time_t due)
      : transactionID(std::move(tid)), bookID(std::move(bid)),
        memberID(std::move(mid)), date(d), type(t), dueDate(due) {}

  string getTransactionID() const { return transactionID; }
  TransactionType getType() const { return type; }

  // Calculates the fine
  double calculateFine(time_t returnDate) const {
    const double finePerDay = 2.0;
    if (returnDate > dueDate) {
      int daysLate = static_cast<int>((returnDate - dueDate) / (60 * 60 * 24));
      return daysLate * finePerDay;
    } else {
      return 0.0;
    }
  }

  // Print the transation details
  void print() const {
    cout << "Transaction " << transactionID << ": "
         << (type == TransactionType::ISSUE ? "Issued" : "Returned") << " book "
         << bookID << " by member " << memberID << "\n";
  }
};

class Library {
private:
  string name;
  string address;

  linkedlist<Book> books;
  linkedlist<Member> members;

  stack<Transaction> recentTransactions;
  queue<Book> reservationQueue;

public:
  Library(string libName, string libAddress)
      : name(std::move(libName)), address(std::move(libAddress)) {}

  // Issue Book
  void issueBook(const string &memberID, const std::string &bookID) {
    Member *m = genericSearch<Member, string>(
        members, memberID,
        [](const Member &mem, const string &id) { return mem.getID() == id; });

    Book *b = genericSearch<Book, string>(
        books, bookID,
        [](const Book &book, const string &id) { return book.getID() == id; });

    if (m && b && b->getAvailability()) {
      m->borrowBook(*b);
      b->setAvailability(false);

      time_t now = std::time(nullptr);
      time_t due = now + (7 * 24 * 60 * 60); // Due in 7 days

      Transaction t("TXN_" + bookID + "_" + memberID, bookID, memberID,
                    TransactionType::ISSUE, now, due);
      recentTransactions.push(t);
    } else {
      cout << "Issue failed: Book may be unavailable or member not found.\n";
    }
  }

  // Return Book
  void returnBook(const string &memberID, const string &bookID,
                  std::time_t actualReturn) {
    Member *m = genericSearch<Member, string>(
        members, memberID,
        [](const Member &mem, const string &id) { return mem.getID() == id; });

    Book *b = genericSearch<Book, string>(
        books, bookID,
        [](const Book &book, const string &id) { return book.getID() == id; });

    if (m && b) {
      m->returnBook(bookID);
      b->setAvailability(true);

      time_t now = std::time(nullptr);
      Transaction t("TXN_" + bookID + "_" + memberID, bookID, memberID,
                    TransactionType::RETURN, now, actualReturn);
      recentTransactions.push(t);

      cout << "Book returned successfully.\n";
    } else {
      cout << "Return failed: Member or book not found.\n";
    }
  }

  // Fine calculation (uses the most recent transaction for simplicity)
  double calculateFine(const std::string &transactionID,
                       std::time_t actualReturn) {
    std::stack<Transaction> tmp = recentTransactions;

    while (!tmp.empty()) {
      const Transaction &t = tmp.top();
      tmp.pop();

      if (t.getTransactionID() == transactionID &&
          t.getType() == TransactionType::ISSUE) {
        return t.calculateFine(actualReturn);
      }
    }
    std::cout << "Transaction not found.\n";
    return 0.0;
  }
  // Report generation with beautification
  void generateReport() {
    cout << "\n===== Library Report =====\n";
    cout << "Library Name: " << name << "\n";
    cout << "Address: " << address << "\n\n";
    cout << "--- Books in Library ---\n";
    books.printfrwd();

    cout << "\n--- Registered Members ---\n";
    members.printfrwd();

    cout << "\n--- Recent Transactions ---\n";
    stack<Transaction> copy = recentTransactions;
    while (!copy.empty()) {
      copy.top().print();
      copy.pop();
    }
    cout << "==========================\n";
  }

  // Add Book or Member (utility for setup)
  void addBook(const Book &book) { books.addback(book); }

  void registerMember(const Member &member) { members.addback(member); }

  // Accessors
  string getName() const { return name; }
  string getAddress() const { return address; }
};

#endif
