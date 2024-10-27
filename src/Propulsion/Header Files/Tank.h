#pragma once
#include <string>

class Tank {
public:
    // Constructor
    Tank(int fuelType, double tankCapacity, double tankFillValue);

    // Method to load tank data from an XML file
    void loadTankFromXML();

    // Getters for the attributes
    int getFuelType() const;
    double getTankCapacity() const;
    double getTankFillValue() const;

private:
    int fuelType;          // Type of fuel (e.g., gasoline, diesel, etc.)
    double tankCapacity;   // Capacity of the tank
    double tankFillValue;  // Current fill value of the tank
};
