
#ifndef FILEMETADATA_H
#define FILEMETADATA_H

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

    void setFileDate(const std::chrono::system_clock::time_point& fileDate);
    std::chrono::system_clock::time_point getFileDate() const;

    void setFlightModelVersion(const std::string& version);
    std::string getFlightModelVersion() const;
};

#endif // FILEMETADATA_H
