#pragma once
#include <string>

class EngineThruster {
public:
    // Constructor
    EngineThruster(const std::string& name, int engineOrThruster, float locationX, float locationY, float orientation);

    // Method to load data from an XML file
    void loadDataFromXML();

    // Getters for the attributes
    const std::string& getName() const;
    int getEngineOrThruster() const;
    float getLocationX() const;
    float getLocationY() const;
    float getOrientation() const;

private:
    std::string name;        // Name of the engine or thruster
    int engineOrThruster;    // 0 for engine, 1 for thruster
    float locationX;         // X location
    float locationY;         // Y location
    float orientation;       // Orientation in degrees/radians
};