#include "EngineThruster.h"
#include <iostream>

EngineThruster::EngineThruster(const std::string& name, int engineOrThruster, float locationX, float locationY, float orientation)
    : name(name), engineOrThruster(engineOrThruster), locationX(locationX), locationY(locationY), orientation(orientation) {}

void EngineThruster::loadDataFromXML() {
    // TODO: Implement XML loading logic for engine/thruster data
    std::cout << "Loading data from XML..." << std::endl;
}

const std::string& EngineThruster::getName() const {
    return name;
}

int EngineThruster::getEngineOrThruster() const {
    return engineOrThruster;
}

float EngineThruster::getLocationX() const {
    return locationX;
}

float EngineThruster::getLocationY() const {
    return locationY;
}

float EngineThruster::getOrientation() const {
    return orientation;
}
