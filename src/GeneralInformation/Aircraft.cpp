#include "Aircraft.h"
#include <fstream>
#include <iostream>
#include "Validation.h"

// Default constructor
Aircraft::Aircraft() : name(""), Description(""), limitations(""), notes(""), Organization("")  {}

// Set and get functions for name
void Aircraft::setName(const std::string& name) {
    this->name = name;
    // test for the push/pull
}

std::string Aircraft::getName() const {
    return name;
}

// Set and get functions for user
void Aircraft::setUser(const User& user) {
    if (!Validation::validateAuthor(user.getAuthorName()))
    {
        std::cout << "Invalid Author name!" << std::endl;
        return;
    }

    if (!Validation::validateEmail(user.getEmail()))
    {
        std::cout << "Invalid Email input!" << std::endl;
        return;
    }

    if (!Validation::validateOrganization(user.getOrganization()))
    {
        std::cout << "Organization limit must be 100 or fewer!" << std::endl;
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

// Set and get functions for description
void Aircraft::setDescription(std::string description) {
     if (description.length() > 500) {
        std::cout << "Description must be 500 characters or fewer!" << std::endl;
        return;
    }
    this->Description = description;
}

std::string Aircraft::getDescription() {
    return Description;
}

// Set and get functions for limitations
void Aircraft::setLimitations(std::string limitations) {
    if (!Validation::validateLimitations(limitations))
    {
        std::cout << "Limitations must be 400 characters or fewer!" << std::endl;
        return;
    }
    this->limitations = limitations;
}

std::string Aircraft::getLimitations() {
    return limitations;
}

// Set and get functions for notes
void Aircraft::setNotes(std::string notes) {
    if (!Validation::validateNotes(notes))
    {
        std::cout << "Notes must be 500 characters or fewer!" << std::endl;
        return;
    }
    this->notes = notes;
}

std::string Aircraft::getNotes() const {
    return notes;
}

// Save the Aircraft data to a file
void Aircraft::saveToFile() {
    
}

// Load the Aircraft data from a file
Aircraft Aircraft::loadFromFile() {
    Aircraft loadedAircraft;
    return loadedAircraft;
}


void Aircraft::setOrganization(std::string organization) {
    if (organization.length() > 100) {
        std::cout << "Organization name must be 100 characters or fewer!" << std::endl;
        return;
    }
    this->Organization = organization;
}

std::string Aircraft::getOrganization() const {
    return Organization;
}