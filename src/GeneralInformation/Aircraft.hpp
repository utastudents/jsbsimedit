#pragma once

#include <string>
#include <vector>
#include "User.hpp"
#include "FileMetadata.hpp"
#include "Config.hpp"
#include "References.hpp"

class Aircraft {
private:
    std::string name;
    User user;
    FileMetadata fileMetadata;
    Config config;

    std::string Description;
    std::string Organization;

    std::vector<References> references; 
    std::string limitations;                
    std::string notes;                      

public:
    Aircraft();

    void setName(const std::string& name);
    std::string getName() const;

    void setUser(const User& user);
    User getUser() const;

    void setFileMetadata(const FileMetadata& fileMetaData);
    FileMetadata getFileMetadata() const;

    void setConfig(const Config& config);
    Config getConfig() const;

    void setReferences(const std::vector<References>& references);
    std::vector<References> getReferences() const;

    // void setLimitations(const std::string& limitations);
    // std::string getLimitations() const;
    void setDescription(std::string Description);
    std::string getDescription();

    void setNotes(const std::string& notes);
    std::string getNotes() const;

    void setLimitations(std::string limitations);
    std::string getLimitations();

    void setNotes(std::string notes);
    std::string getNotes();

    void saveToFile();
    Aircraft loadFromFile();

    void setOrganization(std::string organization);
    std::string getOrganization() const;

};



