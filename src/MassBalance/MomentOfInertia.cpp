
#include "MomentOfInteria.hpp"
#include <iostream>

namespace MassBalance{

// Fuselage constructor
Fuselage::Fuselage(double mass, double length, double radius) 
    : mass(mass), length(length), radius(radius) {}
// Getters
double Fuselage::getMass() const { return mass; }
double Fuselage::getLength() const { return length; }
double Fuselage::getRadius() const { return radius; }
// Setters
void Fuselage::setMass(double mass) { this->mass = mass; }
void Fuselage::setLength(double length) { this->length = length; }
void Fuselage::setRadius(double radius) { this->radius = radius; }
// Inertia axes
double Fuselage::inertiaAboutLongitudinalAxis() const {
        return 0.5 * mass * radius * radius;
    }
double Fuselage::inertiaAboutTransverseAxis() const {
        return (1.0 / 12.0) * mass * (3 * radius * radius + length * length);
    }

// Wing constructor
Wing::Wing(double mass, double span, double chord)
    : mass(mass), span(span), chord(chord) {}
// Getters
double Wing::getMass() const { return mass; }
double Wing::getSpan() const { return span; }
double Wing::getChord() const { return chord; }
// Setters
void Wing::setMass(double mass) { this->mass = mass; }
void Wing::setSpan(double span) { this->span = span; }
void Wing::setChord(double chord) { this->chord = chord; }
// Inertia axes
double Wing::inertiaAboutRootAxis() const {
        return (1.0 / 3.0) * mass * span * span;
    }
double Wing::inertiaAboutSpanwiseAxis() const {
        return (1.0 / 12.0) * mass * (span * span + chord * chord);
    }

// Tail constructor
Tail::Tail(double mass, double span, double chord)
    : mass(mass), span(span), chord(chord) {}
// Getters
double Tail::getMass() const { return mass; }
double Tail::getSpan() const { return span; }
double Tail::getChord() const { return chord; }
// Setters
void Tail::setMass(double mass) { this->mass = mass; }
void Tail::setSpan(double span) { this->span = span; }
void Tail::setChord(double chord) { this->chord = chord; }
// Inertia axes
double Tail::inertiaAboutCenterAxis() const {
        return (1.0 / 12.0) * mass * (span * span + chord * chord);
    }
double Tail::inertiaAboutRootAxis() const {
        return (1.0 / 3.0) * mass * span * span;
    }

// Airplane constructor
Airplane::Airplane(Fuselage fuselage, Wing leftWing, Wing rightWing, Tail tail)
    : fuselage(fuselage), leftWing(leftWing), rightWing(rightWing), tail(tail),
      inertiaUnits("SLUG*FT2") {
    // Compute initial inertia values in SLUG*FT2
    totalInertiaLongitudinal = fuselage.inertiaAboutLongitudinalAxis()
                             + leftWing.inertiaAboutSpanwiseAxis()
                             + rightWing.inertiaAboutSpanwiseAxis()
                             + tail.inertiaAboutCenterAxis();

    totalInertiaTransverse = fuselage.inertiaAboutTransverseAxis()
                           + leftWing.inertiaAboutRootAxis()
                           + rightWing.inertiaAboutRootAxis()
                           + tail.inertiaAboutRootAxis();

    totalInertiaVertical = fuselage.inertiaAboutTransverseAxis()  // Approximation for vertical axis
                         + leftWing.inertiaAboutSpanwiseAxis()
                         + rightWing.inertiaAboutSpanwiseAxis()
                         + tail.inertiaAboutCenterAxis();
}

// Getters for total inertia
double Airplane::totalInertiaAboutLongitudinalAxis() const {
    return totalInertiaLongitudinal;
}

double Airplane::totalInertiaAboutTransverseAxis() const {
    return totalInertiaTransverse;
}

double Airplane::totalInertiaAboutVerticalAxis() const {
    return totalInertiaVertical;
}

// Setters for total inertia
void Airplane::setTotalInertiaAboutLongitudinalAxis(double inertia) {
    totalInertiaLongitudinal = inertia;
}
void Airplane::setTotalInertiaAboutTransverseAxis(double inertia) {
    totalInertiaTransverse = inertia;
}
void Airplane::setTotalInertiaAboutVerticalAxis(double inertia) {
    totalInertiaVertical = inertia;
}

// Getter for inertia units
std::string Airplane::getInertiaUnits() const {
    return inertiaUnits;
}

// Setter for inertia units
void Airplane::setInertiaUnits(const std::string& units) {
    inertiaUnits = units;
}

// Conversion function between SLUG*FT2 and KG*M2
void Airplane::convertInertiaUnits() {
    if (inertiaUnits == "SLUG*FT2") {
        // Convert from SLUG*FT2 to KG*M2
        totalInertiaLongitudinal *= 1.3558179;
        totalInertiaTransverse *= 1.3558179;
        totalInertiaVertical *= 1.3558179;
        inertiaUnits = "KG*M2";
    } else if (inertiaUnits == "KG*M2") {
        // Convert from KG*M2 to SLUG*FT2
        totalInertiaLongitudinal /= 1.3558179;
        totalInertiaTransverse /= 1.3558179;
        totalInertiaVertical /= 1.3558179;
        inertiaUnits = "SLUG*FT2";
    }
}

}
