#include "Thruster.hpp"
#include <iostream>

Thruster::Thruster(const std::string& name, int engineOrThruster, float locationX, float locationY, float orientation, double thrust, const std::string& thrustUnit)
    : EngineThruster(name, engineOrThruster, locationX, locationY, orientation), thrust(thrust), thrustUnit(thrustUnit) {}

void Thruster::loadThrusterFromXML() {
    // TODO: Implement XML loading logic for thruster data
    std::cout << "Loading thruster data from XML..." << std::endl;
}

double Thruster::getThrust() const {
    return thrust;
}

const std::string& Thruster::getThrustUnit() const {
    return thrustUnit;
}
