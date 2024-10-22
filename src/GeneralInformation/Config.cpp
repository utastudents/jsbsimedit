#include "Config.h"

//Default constructor
Config::Config() : releaseLevel(""), configVersion(""), flightModelVersion("") {}

// Set and get functions for releaseLevel
void Config::setReleaseLevel(const std::string& releaseLevel) {
    this->releaseLevel = releaseLevel;
}

std::string Config::getReleaseLevel() const {
    return releaseLevel;
}

// Set and get functions for configVersion
void Config::setConfigVersion(const std::string& configVersion) {
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
