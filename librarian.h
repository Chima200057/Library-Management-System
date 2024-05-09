#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <string>
#include "book.h"
#include "member.h"
#include <fstream>

class Librarian {
public:
    Librarian();
    ~Librarian();

    void addMember(const Member& member);
    bool issueBook(int bookID, int memberID);
    void returnBook(int bookID);
    void displayBorrowedBooks(int memberID);
    double calculateFine(int bookID);

private:
    const int MAX_BOOKS = 200;
    const int MAX_MEMBERS = 200;

    Book* books_;
    int numBooks_;

    Member* members_;
    int numMembers_;

    void readBooksFromFile(const std::string& filePath);
    void writeBooksToFile(const std::string& filePath);
};

#endif // LIBRARIAN_H
