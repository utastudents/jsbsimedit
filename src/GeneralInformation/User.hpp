#pragma once

#include <string>

class User {
private:
    std::string authorName;
    std::string email;
    std::string organization;

public:
    User();

    void setAuthorName(const std::string& name);
    std::string getAuthorName() const;

    void setEmail(const std::string& email);
    std::string getEmail() const;

    void setOrganization(const std::string& organization);
    std::string getOrganization() const;
};