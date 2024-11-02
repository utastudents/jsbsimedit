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

void Component::inputOverpressure(double overpressure) { maxOverpressure = overpressure; }
void Component::inputValveCoefficient(double valveCoefficient) { this->valveCoefficient = valveCoefficient; }
void Component::inputInitialFullness(double initFullness) { fullness = initFullness; }

std::string Component::unitToString(Unit unit) {
    switch (unit) {
        // include all cases for each enum type and return appropriate string
        default: return "Unknown Unit";
    }
}
