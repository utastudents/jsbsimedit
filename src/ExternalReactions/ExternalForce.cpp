#include "ExternalForce.hpp"

// Constructor with default values
Force::forceVector::forceVector(float x_val, float y_val, float z_val)
    : x(x_val), y(y_val), z(z_val) {}

// Constructor for Force class
Force::Force(forceVector direction, forceVector location)
    : Direction(direction), Location(location), frameType(BODY) {}

// Destructor
Force::~Force() {}

// Applies the force (currently a placeholder)
void Force::applyForce() {}

// Returns the force name
string Force::forceName(string name) {
    return name;
}

// Converts location units 
double locationUnits(double units) {
    return units;
}

// Changes the frame of reference
void Force::changeFrame(Frame newFrame) {
    frameType = newFrame;
}

