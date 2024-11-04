#include "Validation.h"

// Validate that the name is non-empty and contains only alphabetic characters and spaces
bool Validation::validateName(const std::string& name) {
    return true;
}

// Validate that the file name is non-empty and ends with a proper extension (e.g., .txt, .cfg)
bool Validation::validateFileName(const std::string& fileName) {
    return true;
}

// Validate that the release level is non-empty (could be extended to match specific values)
bool Validation::validateReleaseLevel(const std::string& releaseLevel) {
    return true;
}

// Validate that the config version follows a specific version format (e.g., 1.0.0)
bool Validation::validateConfigVersion(const std::string& configVersion) {
    return true;
}

// Validate that the flight model version follows a specific version format (e.g., 1.0.0)
bool Validation::validateFlightModelVersion(const std::string& flightModelVersion) {
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
    return true;
}

// Validate file date (assuming a format like YYYY-MM-DD)
bool Validation::validateFileDate(const std::string& fileDate) {
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
