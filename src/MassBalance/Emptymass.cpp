#include "Emptymass.hpp"
#include <iostream>

//constructor
EmptyMass::EmptyMass(float massValue, const std::string& unitMeasure)
    : emptyMass(massValue), units(unitMeasure) {}

//setters
void EmptyMass::setEmptyMass(float massValue) {
    emptyMass = massValue;
}


void EmptyMass::setUnits(const std::string& unitMeasure) {
    units = unitMeasure;
}

//getters
float EmptyMass::getEmptyMass() const {
    return emptyMass;
}


std::string EmptyMass::getUnits() const {
    return units;
}

