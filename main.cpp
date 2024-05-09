#include <string>
#include "librarian.h"
#include <iostream>

int main() {
    Librarian librarian;

    // Main menu loop
    while (true) {
        // Print menu options
        std::cout << "\n** Welcome to the Library **\n";
        std::cout << "1. Add a Member" << std::endl;
        std::cout << "2. Issue a Book" << std::endl;
        std::cout << "3. Return a Book" << std::endl;
        std::cout << "4. Display Borrowed Books for a Member" << std::endl;
        std::cout << "5. Calculate Fine for Overdue Books" << std::endl;
        std::cout << "6. Exit" << std::endl;

        // Get user choice
        int choice;
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        // Handle user input and call relevant functions
        switch (choice) {
            case 1: {
                // Provide member details
                int memberId;
                std::string memberName;
                std::string memberAddress;
                std::string memberEmail;

                // Get member details from the user
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;
                std::cout << "Enter Member Name: ";
                std::cin.ignore(); // Ignore newline character from previous input
                std::getline(std::cin, memberName);
                std::cout << "Enter Member Address: ";
                std::getline(std::cin, memberAddress);
                std::cout << "Enter Member Email: ";
                std::cin >> memberEmail;

                Member newMember(memberId, memberName, memberAddress, memberEmail);
                librarian.addMember(newMember);
                break;
            }
            case 2: {
                // Provide book and member details
                int bookIdToIssue;
                int memberIDToIssue;

                // Get details from the user
                std::cout << "Enter Book ID to issue: ";
                std::cin >> bookIdToIssue;
                std::cout << "Enter Member ID to issue: ";
                std::cin >> memberIDToIssue;

                librarian.issueBook(bookIdToIssue, memberIDToIssue);
                break;
            }
            case 3: {
                // Provide book details
                int bookIDToReturn;

                // Get details from the user
                std::cout << "Enter Book ID to return: ";
                std::cin >> bookIDToReturn;

                librarian.returnBook(bookIDToReturn);
                break;
            }
            case 4: {
                // Provide member details
                int memberIDToDisplay;

                // Get details from the user
                std::cout << "Enter Member ID to display borrowed books: ";
                std::cin >> memberIDToDisplay;

                librarian.displayBorrowedBooks(memberIDToDisplay);
                break;
            }
            case 5: {
                // Provide book details
                int bookIDToCalculateFine;

                // Get details from the user
                std::cout << "Enter Book ID to calculate fine: ";
                std::cin >> bookIDToCalculateFine;

                librarian.calculateFine(bookIDToCalculateFine);
                break;
            }
            case 6:
                std::cout << "\nExiting...\n";
                return 0;
            default:
                std::cout << "\nInvalid choice. Please enter a number between 1 and 6." << std::endl;
                break;
        }
    }

    return 0;
}
