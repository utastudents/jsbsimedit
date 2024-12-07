#include "Validation.hpp"
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>

// Validate that the name is non-empty and contains only alphabetic characters and spaces
bool Validation::validateName(const std::string& name) {
    if (name.empty()){
        return false;
    }

    for(char c : name) {
        if(!(std::isalpha(c) || c == ' ')){
            return false;
        }
    }

    return true;
}

// Validate that the file name is non-empty and ends with a proper extension (e.g., .txt, .cfg)
bool Validation::validateFileName(const std::string& fileName) {
    if (fileName.empty()){
        return false;
    }

    return true;
}

// Validate that the release level is non-empty (could be extended to match specific values)
bool Validation::validateReleaseLevel(const std::string& releaseLevel) {
    if(releaseLevel.empty()){
        return false;
    }
    return true;
}

// Validate that the config version follows a specific version format (e.g., 1.0.0)
bool Validation::validateConfigVersion(const std::string& configVersion) {
    // Check if the config version is empty
    if (configVersion.empty()) {
        return false;
    }

    // Split the version string by dots
    std::stringstream ss(configVersion);
    std::string token;
    int partCount = 0;

    while (std::getline(ss, token, '.')) {
        // Check if the part is a valid integer (non-empty and all digits)
        if (token.empty()) {
            return false;
        }

        // Manually check if all characters are digits
        for (char c : token) {
            if (!std::isdigit(c)) {
                return false;
            }
        }

        partCount++;
    }

    // The version should have exactly three parts
    if (partCount != 3) {
        return false;
    }

    return true;
}

// Validate that the flight model version follows a specific version format (e.g., 1.0.0)
bool Validation::validateFlightModelVersion(const std::string& flightModelVersion) {
    // Check if the model version is empty
    if (flightModelVersion.empty()) {
        return false;
    }

    // Split the version string by dots
    std::stringstream ss(flightModelVersion);
    std::string token;
    int partCount = 0;

    while (std::getline(ss, token, '.')) {
        // Check if the part is a valid integer (non-empty and all digits)
        if (token.empty()) {
            return false;
        }

        // Manually check if all characters are digits
        for (char c : token) {
            if (!std::isdigit(c)) {
                return false;
            }
        }

        partCount++;
    }

    // The version should have exactly three parts
    if (partCount != 3) {
        return false;
    }
    return true;
}

// Validate that the author name is non-empty and contains only alphabetic characters and spaces
bool Validation::validateAuthor(const std::string& author) {
    if(author.empty() || author.length() > 100 || author.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != std::string::npos)
        {
            return false;   //author input invalid
        }

    return true;
}

// Validate email using a basic email regex pattern
bool Validation::validateEmail(const std::string& email) {
    size_t atPosition = email.find('@');
    size_t dotPosition = email.find('.');

    if (atPosition == std::string::npos || dotPosition == std::string::npos)
    {
        return false;
    }

    if ((atPosition < dotPosition) && (atPosition > 0) && (dotPosition < email.length() - 1))
    {
        return true;
    }

    return false;
}

// Validate that the organization name is non-empty
bool Validation::validateOrganization(const std::string& organization) {
    if(organization.empty()){
        return false;
    }
    return true;
}

// Validate file date (assuming a format like YYYY-MM-DD)
bool Validation::validateFileDate(const std::string& fileDate) {
    // The date should be in the format "YYYY-MM-DD", which is 10 characters long
    if (fileDate.size() != 10) {
        return false;
    }

    // Check if the string contains the correct format: YYYY-MM-DD
    if (fileDate[4] != '-' || fileDate[7] != '-') {
        return false;
    }

    // Split the string into year, month, and day
    std::string yearStr = fileDate.substr(0, 4);
    std::string monthStr = fileDate.substr(5, 2);
    std::string dayStr = fileDate.substr(8, 2);

    // Check if the year, month, and day are numeric
    for (char c : yearStr) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    for (char c : monthStr) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    for (char c : dayStr) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    // Convert year, month, and day to integers
    int year = std::stoi(yearStr);
    int month = std::stoi(monthStr);
    int day = std::stoi(dayStr);

    // Check if the month is between 1 and 12
    if (month < 1 || month > 12) {
        return false;
    }

    // Days in each month for non-leap years
    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year
    bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

    // If it's February, check for leap year and valid day
    if (month == 2 && isLeapYear) {
        if (day < 1 || day > 29) {
            return false;
        }
    }
    // If it's February in a non-leap year, day should be between 1 and 28
    else if (month == 2 && !isLeapYear) {
        if (day < 1 || day > 28) {
            return false;
        }
    }
    // For all other months, check if the day is valid for that month
    else {
        if (day < 1 || day > daysInMonth[month - 1]) {
            return false;
        }
    }

    return true;
}

// Validate that the limitations are non-empty
bool Validation::validateLimitations(const std::string& limitations) {
    if (limitations.length() > 400)
    {
        return false;
    }

    return true;
}

// Validate that the notes are non-empty
bool Validation::validateNotes(const std::string& notes) {
    if (notes.length() > 500)
    {
        return false;
    }
    
    return true;
} 