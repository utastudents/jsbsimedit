#include "Component.hpp"
#include <iostream>

int Component::ballonetCount = 0;
// Component methods
// Constructor
Component::Component() : location{0,0,0},
	                     dimensions{0,0,0}
{
    maxOverpressure = 0;
    fullness = 0;
    valveCoefficient = 0;
    gasType = GasType::AIR;
    hasHeat = false;
}

void Component::setGasType(GasType type) {
    gasType = type;
}

void Component::setLocationUnit(Unit type) { 
    locationUnit = type;
}

void Component::setDimensionsUnit(Unit type) { 
    dimensionsUnit = type;
}

void Component::setDimensionsShape(Unit shape) {
    dimensionsShape = shape;
}

void Component::setPressureUnit(Unit type) { 
    pressureUnit = type;
}

void Component::setValveCoefficientUnit(Unit type) {
    valveCoefficientUnit = type;
}

// Set location
void Component::setLocation(double locationX, double locationY, double locationZ) {
    location[0] = locationX;
    location[1] = locationY;
    location[2] = locationZ;
}

// Set dimensions
void Component::setDimensions(double dimensionX, double dimensionY, double dimensionZ) {
    dimensions[0] = dimensionX;
    dimensions[1] = dimensionY;
    dimensions[2] = dimensionZ;
}

// Set Methods
void Component::setOverpressure(double overpressure) { 
    maxOverpressure = overpressure; 
}

void Component::setValveCoefficient(double valveCoefficient) { 
    this->valveCoefficient = valveCoefficient; 
}

void Component::setInitialFullness(double initFullness) { 
    fullness = initFullness; 
}

void Component::setName(std::string newName) {
    name = newName;
}

// Get Methods
Component::GasType Component::getGasType() const {
    return gasType;
}

Component::Unit Component::getLocationUnit() const {
    return locationUnit;
}

Component::Unit Component::getDimensionsUnit() const {
    return dimensionsUnit;
}

Component::Unit Component::getDimensionsShape() const {
    return dimensionsShape;
}

Component::Unit Component::getPressureUnit() const {
    return pressureUnit;
}

Component::Unit Component::getValveCoefficientUnit() const {
    return valveCoefficientUnit;
}

std::vector<double> Component::getLocation() const {
    return { location[0], 
             location[1], 
             location[2] };
}

std::vector<double> Component::getDimensions() const {
    return { dimensions[0], 
             dimensions[1], 
             dimensions[2] };
}

double Component::getOverpressure() const { 
    return maxOverpressure; 
}

double Component::getValveCoefficient() const { 
    return valveCoefficient; 
}

double Component::getInitialFullness() const { 
    return fullness; 
}

std::string Component::getName() const { 
    return name; 
}

// Unit to string conversion
std::string Component::unitToString(Unit unit) {
    switch (unit) {
        case Unit::WIDTH:           return "width";
        case Unit::RADIUS:          return "radius";

        case Unit::PA:              return "PA";
        case Unit::PSI:             return "PSI";
        
        case Unit::M:               return "M";
        case Unit::IN:              return "IN";
        
        case Unit::FT4_SEC_SLUG:    return "FT4*SEC/SLUG";
        case Unit::M4_SEC_KG:       return "M4*SEC/KG";
        
        case Unit::LBS_FT_SEC:      return "lbs ft / sec";
        case Unit::LB_FT_SEC_R:     return "lb ft / (sec R)";
        
        case Unit::FT3_SEC:         return "ft^3 / sec";
    }
}

void Component::setBallonetCount(int count) 
{ 
    ballonetCount=count; 
}

int Component::getBallonetCount() 
{ 
    return ballonetCount; 
}