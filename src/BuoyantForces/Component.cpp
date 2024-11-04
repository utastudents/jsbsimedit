#include "Component.hpp"
#include <iostream>

// Component methods
Component::Component() 
    : maxOverpressure(0.0), fullness(0.0), valveCoefficient(0.0, 0.0), gasType(air), 
      location(0.0, 0.0, 0.0), dimensions(0.0, 0.0, 0.0), volume(0.0), 
      temperature(0.0), pressure(0.0), mass(0.0), hasHeat(false) {}

// Set location
void Component::setLocation(double x, double y, double z) {
    location[0] = x;
    location[1] = y;
    location[2] = z;
}

// Set dimensions
void Component::setDimensions(double x, double y, double z) {
    dimensions[0] = x;
    dimensions[1] = y;
    dimensions[2] = z;
}

// Input methods
void Component::inputOverpressure(double overpressure) { maxOverpressure = overpressure; }
void Component::inputValveCoefficient(double valveCoefficient) { this->valveCoefficient = valveCoefficient; }
void Component::inputInitialFullness(double initFullness) { fullness = initFullness; }

// Unit to string conversion
std::string Component::unitToString(Unit unit) {
    switch (unit) {
        // include all cases for each enum type and return appropriate string
        default: return "Unknown Unit";
    }
}

// GasCell methods
GasCell::GasCell(double v, double t, double p, double m) : Component() {
    volume = v;
    temperature = t;
    pressure = p;
    mass = m;
}

GasCell::~GasCell() {
    // Destructor definition
}

// Ballonet methods
Ballonet::Ballonet(const std::string& name, GasType gastype) {
    this->name = name;
    this->gasType = gastype;
}

Ballonet::~Ballonet() {
    // Destructor definition
}

int Ballonet::getBallonetNumber() { return ballonetCount; }

void Ballonet::createBallonetTab(int tabIndex) {
    // Implementation for creating Ballonet Tab
}

void Ballonet::inputBlowerValue(double blowerValue) { this->blowerValue = blowerValue; }

