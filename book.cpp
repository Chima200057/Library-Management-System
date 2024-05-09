#include <string>
#include "book.h"

int Book::getBookID() const {
    return id_;
}

int Book::getBorrowerID() const {
    return borrowerID_;
}

void Book::setBorrowerID(int borrowerID) {
    borrowerID_ = borrowerID;
}

void Book::setDueDate(const std::string& dueDate) {
    dueDate_ = dueDate;
}



// Constructor and destructor
Book::Book(int id, std::string name, std::string author, std::string type, int pageCount)
    : id_(id), name_(name), author_(author), type_(type), pageCount_(pageCount), borrowerID_(0), dueDate_("") {}

Book::Book() {}

// Getters and setters
// ... (already implemented in the header file)

// Other methods
bool Book::isAvailable() const {
    return borrowerID_ == 0; // Book is available if it has no borrower
}

std::string Book::toString() const {
    std::string availability = isAvailable() ? "Available" : "Borrowed";
    return "Book ID: " + std::to_string(id_) + "\n"
           + "Name: " + name_ + "\n"
           + "Author: " + author_ + "\n"
           + "Type: " + type_ + "\n"
           + "Page Count: " + std::to_string(pageCount_) + "\n"
           + "Availability: " + availability + "\n"
           + "Borrower ID: " + std::to_string(borrowerID_) + "\n"
           + "Due Date: " + dueDate_;
}
