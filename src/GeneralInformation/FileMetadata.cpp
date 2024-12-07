#include "FileMetadata.hpp"
#include <iostream>

// Default constructor
FileMetadata::FileMetadata() : fileName(""), fileDate(std::chrono::system_clock::now()), flightModelVersion("") {}


// Set and get functions for fileName
void FileMetadata::setFileName(const std::string& fileName) {
    this->fileName = fileName;
}

std::string FileMetadata::getFileName() const {
    return fileName;
}

// Set and get functions for fileDate
void FileMetadata::setFileDate(const std::string& fileDate) {
    if (fileDate.empty() || fileDate.find('-') == std::string::npos) {
        std::cerr << "Error: File date must follow the format YYYY-MM-DD." << std::endl;
        return;
    }
    this->fileDate = fileDate;
}

std::chrono::system_clock::time_point FileMetadata::getFileDate() const {
    return fileDate;
}

// Set and get functions for flightModelVersion
void FileMetadata::setFlightModelVersion(const std::string& version) {
    this->flightModelVersion = version;
}

std::string FileMetadata::getFlightModelVersion() const {
    return flightModelVersion;
}
