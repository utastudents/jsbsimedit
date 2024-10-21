#include "Components.hpp"
#include <iostream>

// Constructor
Component::Component() {
    // include any default values for attributes
}

void Component::setLocation(double x, double y, double z) {
    
}

void Component::setDimensions(double x, double y, double z) {

}

void Component::inputOverpressure(double overpressure) {

}

void Component::inputValveCoefficient(double valveCoefficient) {

}

void Component::inputInitialFullness(double fullness) {

}

void Component::selectMeasurementUnits(const std::string& unit) {
    
}

// Constructor
GasCell::GasCell(double v, double t, double p, double m) : Component() {
    // set attributes to provided parameters
}
