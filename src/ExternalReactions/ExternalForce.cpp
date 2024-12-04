#include "ExternalForce.hpp"

// Constructor with default values for forceVector
Force::forceVector::forceVector(float x_val, float y_val, float z_val)
    : x(x_val), y(y_val), z(z_val) {}

// Constructor for Force class
Force::Force(forceVector direction, forceVector location)
    : Direction(direction), Location(location), frameType(BODY) {}

// Destructor
Force::~Force() {}

// Method to apply force (currently placeholder)
void Force::applyForce() {
    // Logic to apply force can be added here
}

// Sets or gets the force name
string Force::forceName(const string& name) {
    // Optionally add validation logic for the name here
    return name;
}

// Converts location units (currently placeholder)
double Force::locationUnits(double units) {
    // Optionally add unit conversion logic here
    return units;
}

// Changes the frame of reference
void Force::changeFrame(const Frame& newFrame) {
    frameType = newFrame;
}
