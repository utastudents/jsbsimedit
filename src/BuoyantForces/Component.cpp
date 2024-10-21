#include "Component.hpp"
#include <iostream>

// Component methods
Component::Component() {
    // Constructor
    // include any default values for attributes
}

void Component::setLocation(double x, double y, double z) {
    location[0] = x;
    location[1] = y;
    location[2] = z;
}

void Component::setDimensions(double x, double y, double z) {
    dimensions[0] = x;
    dimensions[1] = y;
    dimensions[2] = z;
}

void Component::inputOverpressure(double overpressure) { overPressure = overpressure; }
void Component::inputValveCoefficient(double valveCoefficient) { valveCoefficient = valveCoefficient; }
void Component::inputInitialFullness(double fullness) { fullness = fullness; }
// void Component::selectMeasurementUnits(const std::string& unit) { }


// GasCell methods
GasCell::GasCell(double v, double t, double p, double m) : Component() {
    // Constructor
    // set attributes to provided parameters
}

GasCell::~GasCell() {
    // Destructor definition
}


// Ballonet methods
Ballonet::~Ballonet() {
    // Destructor definition
}
