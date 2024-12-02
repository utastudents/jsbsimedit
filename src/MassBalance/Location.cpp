#include "Location.hpp"
#include <iostream>

namespace MassBalance {

// Constructor
Location::Location(double x, double y, double z, const std::string &units)
    : x(x), y(y), z(z), units(units) {}

// setters
void Location::setLocation(double newX, double newY, double newZ) {
  x = newX;
  y = newY;
  z = newZ;
}
void Location::setX(double newX) { x = newX; }

void Location::setY(double newY) { y = newY; }

void Location::setZ(double newZ) { z = newZ; }

void Location::setUnits(const std::string &unitMeasure) { units = unitMeasure; }

// getters
double Location::getX() const { return x; }

double Location::getY() const { return y; }

double Location::getZ() const { return z; }

std::string Location::getUnits() const { return units; }

void Location::convertLengthUnits() {
  if (units == "in") {
    x *= 2.54f; // inches to centimeters
    y *= 2.54f;
    z *= 2.54f;
    units = "cm"; // update the unit to "cm"
  } else if (units == "cm") {
    x /= 2.54f; // entimeters to inches
    y /= 2.54f;
    z /= 2.54f;
    units = "in"; // update the unit to "in"
  }
}

} // namespace MassBalance