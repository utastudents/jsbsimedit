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

void Component::inputOverpressure(double max_overpressure) { overPressure = max_overpressure; }
void Component::inputValveCoefficient(double valveCo) { valveCoefficient = valveCo; }
void Component::inputInitialFullness(double initFullness) { fullness = initFullness; }


// GasCell methods
GasCell::GasCell(double v, double t, double p, double m) : Component() {
    // Constructor
    // set attributes to provided parameters
}

GasCell::~GasCell() {
    // Destructor definition
}


// Ballonet methods
Ballonet::Ballonet(const std::string& name, GasType gastype) {
    // Constructor
}

Ballonet::~Ballonet() {
    // Destructor definition
}

int Ballonet::getBallonetNumber() { return ballonetCount; }

void Ballonet::createBallonetTab(int tabIndex) {

}

void Ballonet::inputBlowerValue(double blowerVal) { blowerValue = blowerVal; }

