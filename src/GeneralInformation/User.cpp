#include "User.h"

// Default constructor
User::User() : authorName(""), email(""), organization("") {}

// Set and get functions for authorName
void User::setAuthorName(const std::string& name) {
    this->authorName = name;
}

std::string User::getAuthorName() const {
    return authorName;
}

// Set and get functions for email
void User::setEmail(const std::string& email) {
    this->email = email;
}

std::string User::getEmail() const {
    return email;
}

// Set and get functions for organization
void User::setOrganization(const std::string& organization) {
    this->organization = organization;
}

std::string User::getOrganization() const {
    return organization;
}
