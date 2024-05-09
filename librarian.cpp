#include "librarian.h"
#include "book.h"
#include "member.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <vector>

int daysBetween(const std::tm& start, const std::tm& end) {
    auto start_time = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&start)));
    auto end_time = std::chrono::system_clock::from_time_t(std::mktime(const_cast<std::tm*>(&end)));

    return std::chrono::duration_cast<std::chrono::hours>(end_time - start_time).count() / 24;
}

Librarian::Librarian() : numBooks_(0), numMembers_(0) {
    books_ = new Book[MAX_BOOKS](); // Use default constructor for each element
    numBooks_ = 0;
    members_ = new Member[MAX_MEMBERS](); // Use default constructor for each element
    numMembers_ = 0;



    // Read book data from CSV file initially
    readBooksFromFile("library_books.csv");
}

Librarian::~Librarian() {
    delete[] books_;
    delete[] members_;
}



void Librarian::addMember(const Member& member) {
    if (numMembers_ == MAX_MEMBERS) {
        std::cout << "\nMember list is full. Please remove members before adding new ones." << std::endl;
        return;
    }

    members_[numMembers_] = member;
    numMembers_++;
}

bool Librarian::issueBook(int bookID, int memberID) {
    int bookIndex = -1;
    for (int i = 0; i < numBooks_; ++i) {
        if (books_[i].getBookID() == bookID) {
            bookIndex = i;
            break;
        }
    }
    if (bookIndex == -1) {
        std::cout << "\nBook with ID " << bookID << " not found." << std::endl;
        return false;
    }

    int memberIndex = -1;
    for (int i = 0; i < numMembers_; ++i) {
        if (members_[i].getMemberID() == memberID) {
            memberIndex = i;
            break;
        }
    }
    if (memberIndex == -1) {
        std::cout << "\nMember with ID " << memberID << " not found." << std::endl;
        return false;
    }

    if (!books_[bookIndex].isAvailable()) {
        std::cout << "\nBook with ID " << bookID << " is already borrowed." << std::endl;
        return false;
    }

    books_[bookIndex].setBorrowerID(memberID);
    // Get current date
    std::time_t now = std::time(nullptr);
    std::tm* currentDate = std::localtime(&now);

    // Set due date 10 days from current date
    std::tm dueDate = *currentDate;
    dueDate.tm_mday += 10;

    // Set book's due date
    char formattedDueDate[11];
    std::strftime(formattedDueDate, sizeof(formattedDueDate), "%Y-%m-%d", &dueDate);
    books_[bookIndex].setDueDate(formattedDueDate);

    std::cout << "\nBook successfully issued to member " << members_[memberIndex].getName() << "." << std::endl;
    return true;
}

void Librarian::returnBook(int bookID) {
    for (int i = 0; i < numBooks_; ++i) {
        if (books_[i].getBookID() == bookID) {
            // Get current date (once)
            std::time_t now = std::time(nullptr);
            std::tm* currentDate = std::localtime(&now);

            // Check for overdue status
            std::tm dueDate;
            std::istringstream dueDateStream(books_[i].getDueDate());
            dueDateStream >> std::get_time(&dueDate, "%Y-%m-%d");  // Include <iomanip>

            if (std::mktime(&dueDate) < now) {
                // Calculate fine
                int daysOverdue = daysBetween(*currentDate, dueDate);
                int fineAmount = daysOverdue * 2; // Example: £2 per day

                std::cout << "\nBook is " << daysOverdue << " days overdue. Fine: £" << fineAmount << "." << std::endl;
            } else {
                std::cout << "\nBook returned on time. No fine." << std::endl;
            }

            // Reset borrower ID and due date
            books_[i].setBorrowerID(0);
            books_[i].setDueDate("");

            std::cout << "\nBook with ID " << bookID << " successfully returned." << std::endl;
            return;
        }
    }

    std::cout << "\nBook with ID " << bookID << " not found or not currently borrowed." << std::endl;
}

void Librarian::displayBorrowedBooks(int memberID) {
    int borrowedCount = 0;
    for (int i = 0; i < numBooks_; ++i) {
        if (books_[i].getBorrowerID() == memberID) {
            borrowedCount++;
            std::cout << "\n- " << books_[i].toString() << std::endl;
        }
    }

    if (borrowedCount == 0) {
        std::cout << "\nMember with ID " << memberID << " has not borrowed any books." << std::endl;
    }
}

double Librarian::calculateFine(int bookID) {
    for (int i = 0; i < numBooks_; ++i) {
        if (books_[i].getBookID() == bookID) {
            std::time_t now = std::time(nullptr);
            std::tm currentDate = *std::localtime(&now);

            std::tm dueDate;
            std::istringstream dueDateStream(books_[i].getDueDate());
            dueDateStream >> std::get_time(&dueDate, "%Y-%m-%d");

            int daysOverdue = daysBetween(currentDate, dueDate);
            double fineAmount = daysOverdue * 1.0; // 1 GBP per day fine

            std::cout << "\nBook with ID " << bookID << " is " << daysOverdue << " days overdue. Fine: £" << fineAmount << "." << std::endl;
            return fineAmount;
        }
    }

    std::cout << "\nBook with ID " << bookID << " is not overdue or not found." << std::endl;
    return 0.0;
}

void Librarian::readBooksFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;
            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            int bookID = std::stoi(fields[0]);
            std::string title = fields[1];
            std::string author = fields[2];
            std::string type = fields[3];
            int pageCount = std::stoi(fields[4]);
            

            Book book(bookID, title, author, type, pageCount);
            addBook(book);
        }

        file.close();
    } else {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
}



void Librarian::writeBooksToFile(const std::string& filePath) {
    std::ofstream file(filePath);

    if (file.is_open()) {
        for (int i = 0; i < numBooks_; ++i) {
            // Assuming Book has a toCSVString() function
            file << books_[i].toCSVString() << std::endl;
        }

        file.close();
    } else {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
}