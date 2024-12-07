#include "Config.hpp"
#include <iostream>

//Default constructor
Config::Config() : releaseLevel(""), configVersion(""), flightModelVersion("") {}

// Set and get functions for releaseLevel
void Config::setReleaseLevel(const std::string& releaseLevel) {
    if (releaseLevel.empty()) {
        std::cerr << "Error: Release level cannot be empty." << std::endl;
        return;
    }
    this->releaseLevel = releaseLevel;
}

std::string Config::getReleaseLevel() const {
    return releaseLevel;
}

// Set and get functions for configVersion
void Config::setConfigVersion(const std::string& configVersion) {
    if (configVersion.empty() || configVersion.find('.') == std::string::npos) {
        std::cerr << "Error: Config version must follow a proper format (e.g., 1.0.0)." << std::endl;
        return;
    }
    this->configVersion = configVersion;
}

std::string Config::getConfigVersion() const {
    return configVersion;
}

// Set and get functions for flightModelVersion
void Config::setFlightModelVersion(const std::string& flightModelVersion) {
    this->flightModelVersion = flightModelVersion;
}

std::string Config::getFlightModelVersion() const {
    return flightModelVersion;
}
