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


// Set and get functions for user
void Aircraft::setUser(const User& user) {
    if (!Validation::validateAuthor(user.getAuthorName()))
    {
        // std::cout << "Invalid Author name!" << std::endl;
        return;
    }

    if (!Validation::validateEmail(user.getEmail()))
    {
        // std::cout << "Invalid Email input!" << std::endl;
        return;
    }

    if (!Validation::validateOrganization(user.getOrganization()))
    {
        // std::cout << "Organization limit must be 100 or fewer!" << std::endl;
        return;
    }

    this->user = user;  //Set the user if all validations pass
}

User Aircraft::getUser() const {
    return user;
}

// Set and get functions for fileMetadata
void Aircraft::setFileMetadata(const FileMetadata& fileMetadata) {
    this->fileMetadata = fileMetadata;
}

FileMetadata Aircraft::getFileMetadata() const {
    return fileMetadata;
}

// Set and get functions for config
void Aircraft::setConfig(const Config& config) {
    this->config = config;
}

Config Aircraft::getConfig() const {
    return config;
}

// Set and get functions for references
void Aircraft::setReferences(const std::vector<References>& references) {
    this->references = references;
}

std::vector<References> Aircraft::getReferences() const {
    return references;
}

/*

// Set and get functions for description
void Aircraft::setDescription(std::string description) {
     if (description.length() > 500) {
        // std::cout << "Description must be 500 characters or fewer!" << std::endl;
        return;
    }
    this->Description = description;
}

*/

/*

std::string Aircraft::getDescription() {
    return Description;
}

*/

// Set and get functions for limitations
void Aircraft::setLimitations(std::string limitations) {
    if (!Validation::validateLimitations(limitations))
    {
        // std::cout << "Limitations must be 400 characters or fewer!" << std::endl;
        return;
    }
    this->limitations = limitations;
}

std::string Aircraft::getLimitations() {
    return limitations;
}

/*

// Set and get functions for notes
void Aircraft::setNotes(std::string notes) {
    if (!Validation::validateNotes(notes))
    {
        // std::cout << "Notes must be 500 characters or fewer!" << std::endl;

*/

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

// Save the Aircraft data to a file
void Aircraft::saveToFile() {
     std::ofstream outFile("aircraft_data.txt");
     // need to change the file name as we want. 

    if (!outFile) {
        // std::cout << "Error file!" << std::endl;
        return;
    }

    // put the data for the file such as....  outFile << "Name: " << name << "\n";

    outFile.close();
    // std::cout << "Data saved successfully." << std::endl;
}

// Load the Aircraft data from a file
Aircraft Aircraft::loadFromFile() {
    Aircraft loadedAircraft;
    return loadedAircraft;
}


void Aircraft::setOrganization(std::string organization) {
    if (organization.length() > 100) {
        // std::cout << "Organization name must be 100 characters or fewer!" << std::endl;
    }
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