#ifndef THRUSTER_H
#define THRUSTER_H

#include "EngineThruster.hpp"
#include <string>

class Thruster : public EngineThruster {
public:
    // Constructor
    Thruster(const std::string& name, int engineOrThruster, float locationX, float locationY, float orientation, double thrust, const std::string& thrustUnit);

    // Method to load thruster data from an XML file
    void loadThrusterFromXML();

    // Getters for the new attributes
    double getThrust() const;
    const std::string& getThrustUnit() const;

private:
    double thrust;             // Thrust value
    std::string thrustUnit;    // Unit of thrust (e.g., Newtons, pounds)
};

#endif // THRUSTER_H
