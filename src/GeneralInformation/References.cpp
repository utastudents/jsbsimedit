#include "References.hpp"

// Default constructor
References::References() : refID(""), author(""), title(""), date("") {}

// Set and get functions for refID
void References::setRefID(const std::string& refID) {
    this->refID = refID;
}

std::string References::getRefID() const {
    return refID;
}

// Set and get functions for author
void References::setAuthor(const std::string& author) {
    this->author = author;
}

std::string References::getAuthor() const {
    return author;
}

// Set and get functions for title
void References::setTitle(const std::string& title) {
    this->title = title;
}

std::string References::getTitle() const {
    return title;
}

// Set and get functions for date
void References::setDate(const std::string& date) {
    this->date = date;
}

std::string References::getDate() const {
    return date;
}
