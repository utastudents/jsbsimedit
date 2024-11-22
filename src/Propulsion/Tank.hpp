

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