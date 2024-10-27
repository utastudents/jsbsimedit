#pragma once
#include <map>
#include <string>

class Tank {
public:
    // Constructor
    Tank();

    // Method to prefill default values
    void prefillDefaults(const std::map<std::string, std::string>& defaultValues);

    // Method to show the tank details
    void show() const;

    // Method to close the tank
    void close();

    // Getters for the attributes
    bool isVisible() const;
    const std::map<std::string, std::string>& getDefaultValues() const;

private:
    bool isVisible;                             // Visibility status of the tank
    std::map<std::string, std::string> defaultValues; // Map for default values
};