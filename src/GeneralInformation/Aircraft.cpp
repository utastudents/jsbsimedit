#include "Aircraft.hpp"
#include <fstream>
#include <iostream>
#include "Validation.hpp"


// Default constructor
Aircraft::Aircraft() : name(""), notes(""), description("") {}

// Set and get functions for name
void Aircraft::setName(const std::string& name) {
    if (name.empty()) {
        std::cerr << "Error: Aircraft name cannot be empty." << std::endl;
        return;
    }
    this->name = name;
}

std::string Aircraft::getName() const {
    return name;
}

// Set and get functions for notes
void Aircraft::setNotes(const std::string& notes) {
    if (notes.length() > 500) {
        std::cerr << "Error: Notes exceed the character limit of 500." << std::endl;
        return;
    }
    this->notes = notes;
}

std::string Aircraft::getNotes() const {
    return notes;
}

// Set and get functions for description
void Aircraft::setDescription(const std::string& description) {
    if (description.length() > 1000) {
        std::cerr << "Error: Description exceeds the character limit of 1000." << std::endl;
        return;
    }
    this->description = description;
}

std::string Aircraft::getDescription() const {
    return description;
}