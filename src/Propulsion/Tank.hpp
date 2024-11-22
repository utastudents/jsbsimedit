/*#ifndef TANK_H
#define TANK_H

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

#endif // TANK_H*/

#ifndef TANK_H
#define TANK_H

#include <string>

class Tank {
public:
    Tank(int fuelType, double tankCapacity, double tankFillValue);
    void loadTankFromXML(); // Add this declaration
    // Getters
    int getFuelType() const;
    double getTankCapacity() const;
    double getTankFillValue() const;
    Tank();  
    // Setters
    void setFuelType(int type);
    void setTankCapacity(double capacity);
    void setTankFillValue(double fillValue);

private:
    int fuelType;          // 0 = Fuel, 1 = Water
    double tankCapacity;   // Capacity of the tank
    double tankFillValue;  // Current fill level
};

#endif // TANK_H