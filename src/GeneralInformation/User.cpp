#include "User.h"
#include <iostream>
#include "Validation.h"

// Default constructor
User::User() : authorName(""), email(""), organization("") {}

// Set and get functions for authorName
void User::setAuthorName(const std::string& name) {
    if (!Validation::validateAuthor(name))
    {
        std::cout << "Invalid author name!" << std::endl;
        return;  //Exit early if the name is invalid
    }
    this->authorName = name;    //Only set the value name if it is valid
}

std::string User::getAuthorName() const {
    return authorName;
}

// Set and get functions for email
void User::setEmail(const std::string& email) {
    if (!Validation::validateEmail(email))
    {
        std::cout << "Invalid email!" << std::endl;
        return; //Exit early if the email is invalid
    }
    this->email = email; //Only set the value email if it valid
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
