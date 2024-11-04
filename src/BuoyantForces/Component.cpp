#include "Component.hpp"
#include <iostream>

int Component::ballonetCount = 0;
// Component methods
// Constructor
Component::Component() : maxOverpressure(0.0), 
                         fullness(0.0), 
                         valveCoefficient(0), 
                         gasType(GasType::AIR), 
                         location(0,0,0),
	                     dimensions(0,0,0), 
                         volume(0.0), 
                         temperature(0.0), 
                         pressure(0.0), 
                         mass(0.0),
                         hasHeat(false)
{
}

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
        case Unit::WIDTH:           return "Width";
        case Unit::RADIUS:          return "Radius";
        case Unit::PSI:             return "PSI";
        case Unit::M:               return "Meters";
        case Unit::IN:              return "Inches";
        case Unit::PA:              return "PA";
        case Unit::M4_SEC_KG:       return "m^4 * sec / kg";
        case Unit::FT4_SEC_SLUG:    return "ft^4 * sec / slug";
        case Unit::LB_FT_SEC_R:     return "lb ft / (sec R)";
        case Unit::LBS_FT_SEC:      return "lbs ft / sec";
        case Unit::FT3_SEC:         return "ft^3 / sec";
        default: return "Unknown Unit";
    }
}

int Component::getBallonetCount() { return ballonetCount; }

// // GasCell methods
// GasCell::GasCell(double v, double t, double p, double m) : Component() {
//     volume = v;
//     temperature = t;
//     pressure = p;
//     mass = m;
// }

// GasCell::~GasCell() {
//     // Destructor definition
// }

// // Ballonet methods
// Ballonet::Ballonet(const std::string& name, GasType gastype) {
//     this->name = name;
//     this->gasType = gastype;
// }

// Ballonet::~Ballonet() {
//     // Destructor definition
// }

// std::string Ballonet::getName() { return name; }

// void Ballonet::inputBlowerValue(double blowerValue) { this->blowerValue = blowerValue; }

