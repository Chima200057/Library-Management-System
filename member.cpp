#include <string>
#include "member.h"

int Member::getMemberID() const {
    return id_;
}

std::string Member::getName() const {
    return name_;
}



// Constructor and destructor
Member::Member(int id, std::string name, std::string address, std::string email)
    : id_(id), name_(name), address_(address), email_(email) {}

Member::Member() {}

// Getters and setters
// ... (already implemented in the header file)

// Other methods
std::string Member::toString() const {
    return "Member ID: " + std::to_string(id_) + "\n"
           + "Name: " + name_ + "\n"
           + "Address: " + address_ + "\n"
           + "Email: " + email_;
}
