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
void Component::setLocation(double locationX, double locationY, double locationZ) {
    location[0] = locationX;
    location[1] = locationY;
    location[2] = locationZ;
}

// Set dimensions
void Component::setDimensions(double x, double y, double z) {
    dimensions[0] = x;
    dimensions[1] = y;
    dimensions[2] = z;
}

// Input methods
void Component::setOverpressure(double overpressure) { maxOverpressure = overpressure; }
void Component::setValveCoefficient(double valveCoefficient) { this->valveCoefficient = valveCoefficient; }
void Component::setInitialFullness(double initFullness) { fullness = initFullness; }

// Unit to string conversion
std::string Component::unitToString(Unit unit) {
    switch (unit) {
        // include all cases for each enum type and return appropriate string
        case Unit::WIDTH:           return "Width";
        case Unit::RADIUS:          return "Radius";
        case Unit::PSI:             return "PSI";
        case Unit::M:               return "M";
        case Unit::IN:              return "IN";
        case Unit::PA:              return "PA";
        case Unit::M4_SEC_KG:       return "M4 * SEC / KG";
        case Unit::FT4_SEC_SLUG:    return "FT4 * SEC / SLUG";
        case Unit::LB_FT_SEC_R:     return "LB FT / (SEC R)";
        case Unit::LBS_FT_SEC:      return "LBS FT / SEC";
        case Unit::FT3_SEC:         return "FT3 / SEC";
        default: return "Unknown Unit";
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