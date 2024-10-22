
#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

class Validation {
public:
    static bool validateName(const std::string& name);
    static bool validateFileName(const std::string& fileName);
    static bool validateReleaseLevel(const std::string& releaseLevel);
    static bool validateConfigVersion(const std::string& configVersion);
    static bool validateFlightModelVersion(const std::string& flightModelVersion);
    static bool validateAuthor(const std::string& author);
    static bool validateEmail(const std::string& email);
    static bool validateOrganization(const std::string& organization);
    static bool validateFileDate(const std::string& fileDate);
    static bool validateLimitations(const std::string& limitations);
    static bool validateNotes(const std::string& notes);
};

#endif // VALIDATION_H
