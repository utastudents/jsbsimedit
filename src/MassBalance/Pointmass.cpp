#include "Pointmass.hpp"

namespace MassBalance {

// Constructors
PointMass::PointMass()
    : name(""), locationUnit("IN"), weightUnit("LBS"), x(0.0), y(0.0), z(0.0),
      weight(0.0) {}

PointMass::PointMass(const std::string &newName, const std::string &locUnit,
                     const std::string &wtUnit, double newX, double newY,
                     double newZ, double newWeight)
    : name(newName), locationUnit(locUnit), weightUnit(wtUnit), x(newX),
      y(newY), z(newZ), weight(newWeight) {}

// Getters
std::string PointMass::getName() const { return name; }
std::string PointMass::getLocationUnit() const { return locationUnit; }
std::string PointMass::getWeightUnit() const { return weightUnit; }
double PointMass::getX() const { return x; }
double PointMass::getY() const { return y; }
double PointMass::getZ() const { return z; }
double PointMass::getWeight() const { return weight; }

// Setters
void PointMass::setName(const std::string &newName) { name = newName; }
void PointMass::setLocationUnit(const std::string &locUnit) {
  locationUnit = locUnit;
}
void PointMass::setWeightUnit(const std::string &wtUnit) {
  weightUnit = wtUnit;
}
void PointMass::setX(double newX) { x = newX; }
void PointMass::setY(double newY) { y = newY; }
void PointMass::setZ(double newZ) { z = newZ; }
void PointMass::setWeight(double newWeight) { weight = newWeight; }
} // namespace MassBalance