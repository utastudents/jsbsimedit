#pragma once 

#include <string>
#include <vector>
#include "MainWindow.hpp"


// class FileHandler : public MainWindow {
class FileHandler {
public:
    // Constructor that initializes the FileHandler object with a file path
    explicit FileHandler(const std::string& filePath);

    // Destructor
    ~FileHandler();

    // Function to read configurations from the file and return them as a vector of strings
    std::vector<std::string> readConfigurations();

    // Function to write a vector of configurations (strings) to the file
    void writeConfigurations(const std::vector<std::string>& configs);
    
private:
    // Data member to store the file path
    std::string filePath;
};
