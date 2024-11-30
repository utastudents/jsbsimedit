#include "Emptymass.hpp"
#include <iostream>
namespace MassBalance{
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

//unit conversion
void EmptyMass::convertUnits() {
    if (units == "lbs") {
        emptyMass *= 0.453592; // convert pounds to kilograms
        units = "kgs"; // update the unit to "kgs" to reflect the conversion
    } else if (units == "kgs") {
        emptyMass /= 0.453592; // convert kilograms to pounds
        units = "lbs";
    } 
    
}


}
