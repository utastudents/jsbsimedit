#include "Tank.hpp"
#include <iostream> // For demonstration purposes

// Constructor to initialize a Tank object
// Parameters:
//   int fuelType: Type of fuel (e.g., gasoline, diesel, etc.)
//   double tankCapacity: Capacity of the tank
//   double tankFillValue: Current fill value of the tank
Tank::Tank(int fuelType, double tankCapacity, double tankFillValue)
    : fuelType(fuelType), tankCapacity(tankCapacity), tankFillValue(tankFillValue) {
    // Constructor implementation can include validation or logging if necessary
}
/*Tank::Tank(int fuelType, double tankCapacity, double tankFillValue)
    : fuelType_(fuelType), tankCapacity_(tankCapacity), tankFillValue_(tankFillValue) {}
*/
/*void Tank::loadTankFromXML() {
    // Implement the logic for loading tank data from XML
    std::cout << "Loading tank data from XML..." << std::endl;
}*/

// Method to load tank data from an XML file
// This method will be implemented to parse an XML file and initialize the tank attributes.
// Currently, it is stubbed out and does nothing.
void Tank::loadTankFromXML() {
    // Stub: Implementation will involve reading an XML file and updating the tank attributes
    std::cout << "Loading tank data from XML is not yet implemented." << std::endl;
}

// Getter for the fuel type
// Returns the type of fuel for this tank.
int Tank::getFuelType() const {
    return fuelType;
}

// Getter for the tank capacity
// Returns the maximum capacity of the tank.
double Tank::getTankCapacity() const {
    return tankCapacity;
}

// Getter for the current fill value
// Returns the current fill level of the tank.
double Tank::getTankFillValue() const {
    return tankFillValue;
}


//Setters
void Tank::setFuelType(int type) {
    fuelType = type;
}

void Tank::setTankCapacity(double capacity) {
    tankCapacity = capacity;
}

void Tank::setTankFillValue(double fillValue) {
    tankFillValue = fillValue;
}
