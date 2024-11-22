#include "Location.hpp"
#include <iostream>

namespace MassBalance{

// Constructor 
Location::Location(float x, float y, float z, const std::string& units) 
    : x(x), y(y), z(z), units(units) {}

//setters
void Location::setLocation(float newX, float newY, float newZ) {
    x = newX;
    y = newY;
    z = newZ;
}


void Location::setUnits(const std::string& unitMeasure) {
    units = unitMeasure;
}

//getters
float Location::getX() const {
    return x;
}

float Location::getY() const {
    return y;
}

float Location::getZ() const {
    return z;
}

std::string Location::getUnits() const {
    return units;
}

}