#include "Component.hpp"
#include <iostream>

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
    
}

void Ballonet::inputBlowerValue(double blowerValue) { this->blowerValue = blowerValue; }
