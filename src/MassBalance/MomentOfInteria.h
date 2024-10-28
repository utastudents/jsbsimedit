#ifndef AIRPLANE_MOMENT_OF_INERTIA_H
#define AIRPLANE_MOMENT_OF_INERTIA_H

// Fuselage Class
class Fuselage {
public:
    Fuselage(double mass, double length, double radius);

    double getMass() const;
    double getLength() const;
    double getRadius() const;

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
    Wing(double mass, double span, double chord);

    double getMass() const;
    double getSpan() const;
    double getChord() const;

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
    Tail(double mass, double span, double chord);

    double getMass() const;
    double getSpan() const;
    double getChord() const;

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
    Airplane(Fuselage fuselage, Wing leftWing, Wing rightWing, Tail tail);

    Fuselage getFuselage() const;
    Wing getLeftWing() const;
    Wing getRightWing() const;
    Tail getTail() const;

    // Aggregate moment of inertia about the longitudinal axis
    double totalInertiaAboutLongitudinalAxis() const;

    // Aggregate moment of inertia about the transverse axis
    double totalInertiaAboutTransverseAxis() const;

    // Aggregate moment of inertia about the vertical axis
    double totalInertiaAboutVerticalAxis() const;

private:
    Fuselage fuselage;
    Wing leftWing;
    Wing rightWing;
    Tail tail;
};

#endif // AIRPLANE_MOMENT_OF_INERTIA_H