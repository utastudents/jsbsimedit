#pragma once

#include <string>

class Config {
private:
    std::string releaseLevel;
    std::string configVersion;
    std::string flightModelVersion;

public:
    Config();

    void setReleaseLevel(const std::string& releaseLevel);
    std::string getReleaseLevel() const;

    void setConfigVersion(const std::string& configVersion);
    std::string getConfigVersion() const;

    void setFlightModelVersion(const std::string& flightModelVersion);
    std::string getFlightModelVersion() const;
};