#include "MomentOfInteria.hpp"
#include <iostream>

namespace MassBalance{

//Fuselage constructor
Fuselage::Fuselage(double mass, double length, double radius) 
    : mass(mass), length(length), radius(radius) {}
//Getters
double Fuselage::getMass() const { return mass; }
double Fuselage::getLength() const { return length; }
double Fuselage::getRadius() const { return radius; }
//Inertia axes
double Fuselage::inertiaAboutLongitudinalAxis() const {
        return 0.5 * mass * radius * radius;
    }
double Fuselage::inertiaAboutTransverseAxis() const {
        return (1.0 / 12.0) * mass * (3 * radius * radius + length * length);
    }

//Wing constructor
Wing::Wing(double mass, double span, double chord)
    : mass(mass), span(span), chord(chord) {}
//Getters
double Wing::getMass() const { return mass; }
double Wing::getSpan() const { return span; }
double Wing::getChord() const { return chord; }
//Inertia axes
double Wing::inertiaAboutRootAxis() const {
        return (1.0 / 3.0) * mass * span * span;
    }
double Wing::inertiaAboutSpanwiseAxis() const {
        return (1.0 / 12.0) * mass * (span * span + chord * chord);
    }


//Tail constructor
Tail::Tail(double mass, double span, double chord)
    : mass(mass), span(span), chord(chord) {}
//Getters
double Tail::getMass() const { return mass; }
double Tail::getSpan() const { return span; }
double Tail::getChord() const { return chord; }
//Inertia axes
double Tail::inertiaAboutCenterAxis() const {
        return (1.0 / 12.0) * mass * (span * span + chord * chord);
    }
double Tail::inertiaAboutRootAxis() const {
        return (1.0 / 3.0) * mass * span * span;
    }

//Airplane constructor
Airplane::Airplane(Fuselage fuselage, Wing leftWing, Wing rightWing, Tail tail) 
    : fuselage(fuselage), leftWing(leftWing), rightWing(rightWing), tail(tail) {}
//Getters
Fuselage Airplane::getFuselage() const { return fuselage; }
Wing Airplane::getLeftWing() const { return leftWing; }
Wing Airplane::getRightWing() const { return rightWing; }
Tail Airplane::getTail() const { return tail; }
//Inertia axes
double Airplane::totalInertiaAboutLongitudinalAxis() const {
        return fuselage.inertiaAboutLongitudinalAxis()
             + leftWing.inertiaAboutSpanwiseAxis()
             + rightWing.inertiaAboutSpanwiseAxis()
             + tail.inertiaAboutCenterAxis();
}
double Airplane::totalInertiaAboutTransverseAxis() const {
        return fuselage.inertiaAboutTransverseAxis()
             + leftWing.inertiaAboutRootAxis()
             + rightWing.inertiaAboutRootAxis()
             + tail.inertiaAboutRootAxis();
    }
double Airplane::totalInertiaAboutVerticalAxis() const {
        return fuselage.inertiaAboutTransverseAxis()  // Approximating for vertical axis
             + leftWing.inertiaAboutSpanwiseAxis()
             + rightWing.inertiaAboutSpanwiseAxis()
             + tail.inertiaAboutCenterAxis();
    }

}