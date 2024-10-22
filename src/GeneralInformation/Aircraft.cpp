#include "Aircraft.h"
#include <fstream>
#include <iostream>

// Default constructor
Aircraft::Aircraft() : name(""), Description(""), limitations(""), notes("") {}

// Set and get functions for name
void Aircraft::setName(const std::string& name) {
    this->name = name;
}

std::string Aircraft::getName() const {
    return name;
}

// Set and get functions for user
void Aircraft::setUser(const User& user) {
    this->user = user;
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
    this->Description = description;
}

std::string Aircraft::getDescription() {
    return Description;
}

// Set and get functions for limitations
bool Aircraft::setLimitations(std::string limitations) {
    return true;
}

std::string Aircraft::getLimitations() {
    return limitations;
}

// Set and get functions for notes
bool Aircraft::setNotes(std::string notes) {
    return true;
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
