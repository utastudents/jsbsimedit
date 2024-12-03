#include "Component.hpp"
#include <iostream>

// Constructor
Component::Component() {
    xLocation = 0;
    yLocation = 0;
    zLocation = 0;
    xDimension = 0;
    yDimension = 0;
    zDimension = 0;
    maxOverpressure = 0;
    fullness = 1.0;
    valveCoefficient = 0;

    // Set default attributes
    gasType = GasType::AIR;
    locationUnit = Unit::M;
    dimensionsUnit = Unit::M;
    dimensionsShape = Unit::WIDTH;
    pressureUnit = Unit::PA;
    valveCoefficientUnit = Unit::FT4_SEC_SLUG;
    // hasHeat = false;
}

void Component::setGasType(GasType type) {
    gasType = type;
    std::cout << "   set gas type to " << gasType << std::endl;
}

void Component::setLocationUnit(Unit type) { 
    locationUnit = type;
    std::cout << "   set location unit to " << unitToString(locationUnit) << std::endl;
}

void Component::setDimensionsUnit(Unit type) { 
    dimensionsUnit = type;
    std::cout << "   set dimensions unit to " << unitToString(dimensionsUnit) << std::endl;
}

void Component::setDimensionsShape(Unit shape) {
    dimensionsShape = shape;
    std::cout << "   set dimensions shape to " << unitToString(dimensionsShape) << std::endl;
}

void Component::setPressureUnit(Unit type) { 
    pressureUnit = type;
    std::cout << "   set pressure unit to " << unitToString(pressureUnit) << std::endl;
}

void Component::setValveCoefficientUnit(Unit type) {
    valveCoefficientUnit = type;
    std::cout << "   set valve coefficient unit to " << unitToString(valveCoefficientUnit) << std::endl;
}

void Component::setXLocation(double x) {
    xLocation = x;
    std::cout << "   set x location to " << xLocation << std::endl;
}

void Component::setYLocation(double y) {
    yLocation = y;
    std::cout << "   set y location to " << yLocation << std::endl;
}

void Component::setZLocation(double z) {
    zLocation = z;
    std::cout << "   set z location to " << zLocation << std::endl;
}

void Component::setXDimension(double x) {
    xDimension = x;
    std::cout << "   set x dimension to " << xDimension << std::endl;
}

void Component::setYDimension(double y) {
    yDimension = y;
    std::cout << "   set y dimension to " << yDimension << std::endl;
}

void Component::setZDimension(double z) {
    zDimension = z;
    std::cout << "   set z dimension to " << zDimension << std::endl;
}

// Set Methods
void Component::setOverpressure(double overpressure) { 
    maxOverpressure = overpressure; 
    std::cout << "   set overpressure to " << maxOverpressure << std::endl;
}

void Component::setValveCoefficient(double valveCoefficient) { 
    this->valveCoefficient = valveCoefficient; 
    std::cout << "   set valve coefficient to " << valveCoefficient << std::endl;
}

void Component::setInitialFullness(double initFullness) { 
    fullness = initFullness; 
    std::cout << "   set fullness to " << fullness << std::endl;
}

void Component::setName(std::string newName) {
    name = newName;
    std::cout << "   set name to " << name << std::endl;
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

double Component::getXLocation() const {
    return xLocation;
}

double Component::getYLocation() const {
    return yLocation;
}

double Component::getZLocation() const {
    return zLocation;
}

double Component::getXDimension() const {
    return xDimension;
}

double Component::getYDimension() const {
    return yDimension;
}

double Component::getZDimension() const {
    return zDimension;
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

std::string Component::gasTypeToString(GasType gastype) {
    switch(gastype) {
        case GasType::AIR:              return "AIR";
        case GasType::HELIUM:           return "HELIUM";
        case GasType::HYDROGEN:         return "HYDROGEN";
        
    }
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
