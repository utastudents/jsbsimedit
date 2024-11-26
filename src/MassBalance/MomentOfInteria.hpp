
#pragma once

#include <string>

namespace MassBalance{

// Fuselage Class
class Fuselage {
public:
    Fuselage(double mass = 0, double length = 0, double radius = 0);

    double getMass() const;
    double getLength() const;
    double getRadius() const;

    void setMass(double mass);
    void setLength(double length);
    void setRadius(double radius);

    // Moment of inertia about the longitudinal axis (cylinder model)
    double inertiaAboutLongitudinalAxis() const;

    // Moment of inertia about transverse axis (cylinder model)
    double inertiaAboutTransverseAxis() const;

private:
    double mass;
    double length;
    double radius;
};

// Wing Class
class Wing {
public:
    Wing(double mass = 0, double span = 0, double chord = 0);

    double getMass() const;
    double getSpan() const;
    double getChord() const;

    void setMass(double mass);
    void setSpan(double span);
    void setChord(double chord);

    // Moment of inertia about the root axis (modeled as a flat plate)
    double inertiaAboutRootAxis() const;

    // Moment of inertia about the spanwise axis
    double inertiaAboutSpanwiseAxis() const;

private:
    double mass;
    double span;
    double chord;
};

// Tail Class
class Tail {
public:
    Tail(double mass = 0, double span = 0, double chord = 0);

    double getMass() const;
    double getSpan() const;
    double getChord() const;

    void setMass(double mass);
    void setSpan(double span);
    void setChord(double chord);

    // Moment of inertia about the center axis (modeled as a small wing)
    double inertiaAboutCenterAxis() const;

    // Moment of inertia about the root axis
    double inertiaAboutRootAxis() const;

private:
    double mass;
    double span;
    double chord;
};

// Airplane Class
class Airplane {
public:
    // Constructor
    Airplane(Fuselage fuselage, Wing leftWing, Wing rightWing, Tail tail);

    // Getters for total inertia values
    double totalInertiaAboutLongitudinalAxis() const;
    double totalInertiaAboutTransverseAxis() const;
    double totalInertiaAboutVerticalAxis() const;

    // Setter for total inertia values
    void setTotalInertiaAboutLongitudinalAxis(double inertia);
    void setTotalInertiaAboutTransverseAxis(double inertia);
    void setTotalInertiaAboutVerticalAxis(double inertia);

    // Getter and setter for inertia units
    std::string getInertiaUnits() const;
    void setInertiaUnits(const std::string& units);

    // Function to convert between SLUG*FT2 and KG*M2
    void convertInertiaUnits();

private:
    // Components of the airplane
    Fuselage fuselage;
    Wing leftWing;
    Wing rightWing;
    Tail tail;

    // Total inertia values and their unit
    double totalInertiaLongitudinal;  // Longitudinal axis inertia
    double totalInertiaTransverse;   // Transverse axis inertia
    double totalInertiaVertical;     // Vertical axis inertia
    std::string inertiaUnits;        // Units of inertia (SLUG*FT2 or KG*M2)
};

}
