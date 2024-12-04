#include "Tank.hpp"
#include <iostream> // For demonstration purposes

// Constructor to initialize a Tank object

Tank::Tank(int fuelType, double tankCapacity, double tankFillValue)
    : fuelType(fuelType), tankCapacity(tankCapacity), tankFillValue(tankFillValue) {
    // Constructor implementation can include validation or logging if necessary
}

void Tank::loadTankFromXML() 
{
    // Stub: Implementation will involve reading an XML file and updating the tank attributes
    std::cout << "Loading tank data from XML is not yet implemented." << std::endl;
}


int Tank::getFuelType() const 
{
    return fuelType;
}


double Tank::getTankCapacity() const 
{
    return tankCapacity;
}


double Tank::getTankFillValue() const 
{
    return tankFillValue;
}


//Setters
void Tank::setFuelType(int type) 
{
    fuelType = type;
}

void Tank::setTankCapacity(double capacity) 
{
    tankCapacity = capacity;
}

void Tank::setTankFillValue(double fillValue) 
{
    tankFillValue = fillValue;
}
