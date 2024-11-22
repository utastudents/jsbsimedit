#pragma once

#include <string>

namespace MassBalance{

class Location {
private:
    float x, y, z;           // Coordinates
    std::string units;        // Units of measurement

public:
    // Constructor
    Location(float x = 0.0f, float y = 0.0f, float z = 0.0f, const std::string& units = "meters");

    // Setters
    void setLocation(float newX, float newY, float newZ);
    void setUnits(const std::string& unitMeasure);

    // Getters
    float getX() const;
    float getY() const;
    float getZ() const;
    std::string getUnits() const;

};

}
