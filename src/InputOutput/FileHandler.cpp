#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <vector>

// Constructor definition to initialize the file path.
FileHandler::FileHandler(const std::string& filePath) : filePath(filePath) {}

// Destructor
FileHandler::~FileHandler() {}

/* Function to read configurations from the specified file and return them
as a vector of strings.*/
std::vector<std::string> FileHandler::readConfigurations() { 
    std::ifstream file(this->filePath); // Create an input file stream
    std::vector<std::string> configurations; // Create a vector of strings to hold the configurations read from the file.
    std::string line; 
    while (std::getline(file, line)) {
        configurations.push_back(line); // Add the current line to the configurations.
    }
    file.close(); // Close the file after reading all lines.
    return configurations; 
}

void FileHandler::writeConfigurations(const std::vector<std::string>& configs) {
    std::ofstream file(this->filePath, std::ofstream::trunc);
    for (const auto& config : configs) {
        file << config << std::endl;
    }
    file.close(); // Close the file after writing all configurations.
}
