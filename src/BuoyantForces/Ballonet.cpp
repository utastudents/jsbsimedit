#include "Ballonet.hpp"
#include <iostream>

// Ballonet methods
Ballonet::Ballonet(const std::string& name, GasType gastype) 
{
    this->gasType = gastype;
    this->name = name;
    blowerValue = 0;
    blowerUnits = Component::Unit::FT3_SEC;
}

Ballonet::Ballonet(const std::string& name) {
    this->name = name;
    blowerValue = 0;
    blowerUnits = Component::Unit::FT3_SEC;
}

Ballonet::~Ballonet() {
    blowerValue = 0;
    blowerUnits = Component::Unit::FT3_SEC;
}

void Ballonet::setBlowerValue(double blowerValue) {
    this->blowerValue = blowerValue;
}

void Ballonet::setBlowerUnit(Component::Unit type) {
    blowerUnits = type;
}

double Ballonet::getBlowerValue() const {
    return blowerValue;
}

Component::Unit Ballonet::getBlowerUnit() const {
    return blowerUnits;
}