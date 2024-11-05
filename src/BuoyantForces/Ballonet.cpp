#include "Component.hpp"
#include <iostream>

// Ballonet methods
Ballonet::Ballonet(const std::string& name, GasType gastype) 
{
    this->name = name;
    this->gasType = gastype;
    Component::ballonetCount++;
}

Ballonet::~Ballonet() 
{
}

std::string Ballonet::getName() { return name; }

void Ballonet::inputBlowerValue(double blowerValue) { this->blowerValue = blowerValue; }
