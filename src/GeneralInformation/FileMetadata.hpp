#pragma once

#include <string>
#include <chrono>

class FileMetadata {
private:
    std::string fileName;
    std::chrono::system_clock::time_point fileDate;
    std::string flightModelVersion;

public:
    FileMetadata();

    void setFileName(const std::string& fileName);
    std::string getFileName() const;

void FileMetadata::setFileDate(const std::string& fileDate);
    std::string getFileDate() const;

    void setFlightModelVersion(const std::string& version);
    std::string getFlightModelVersion() const;
};