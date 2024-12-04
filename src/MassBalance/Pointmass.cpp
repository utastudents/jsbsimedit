#include "Pointmass.hpp"

namespace MassBalance {

// Constructor
PointMass::PointMass(const std::string &name, const Location &loc,
                     const EmptyMass &mass)
    : name(name), newLoc(loc), newMass(mass) {}

// Getters
std::string PointMass::getName() const { return name; }

Location PointMass::getLocation() const { return newLoc; }

EmptyMass PointMass::getMass() const { return newMass; }

// Setters
void PointMass::setName(const std::string &newName) { name = newName; }

void PointMass::setLocation(const Location &loc) { newLoc = loc; }

void PointMass::setMass(const EmptyMass &mass) { newMass = mass; }

} // namespace MassBalance