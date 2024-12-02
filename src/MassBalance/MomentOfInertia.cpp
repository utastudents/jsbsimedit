
#include "MomentOfInertia.hpp"
#include <iostream>

namespace MassBalance {

/*// Fuselage constructor
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

  // Longitudinal (Ixx)
  totalInertiaLongitudinal = fuselage.inertiaAboutLongitudinalAxis() +
                             leftWing.inertiaAboutSpanwiseAxis() +
                             rightWing.inertiaAboutSpanwiseAxis() +
                             tail.inertiaAboutCenterAxis();

  // Transverse (Iyy)
  totalInertiaTransverse =
      fuselage.inertiaAboutTransverseAxis() + leftWing.inertiaAboutRootAxis() +
      rightWing.inertiaAboutRootAxis() + tail.inertiaAboutRootAxis();

  // Vertical (Izz)
  totalInertiaVertical =
      fuselage.inertiaAboutTransverseAxis() // Approximation for vertical axis
      + leftWing.inertiaAboutSpanwiseAxis() +
      rightWing.inertiaAboutSpanwiseAxis() + tail.inertiaAboutCenterAxis();

  // Off-diagonal: XZ Plane (Ixz)
  totalInertiaXZPlane = 0.0; // assuming symmetry

  // Off-diagonal: YZ Plane (Iyz)
  totalInertiaYZPlane = 0.0; // Initial contribution from fuselage
  totalInertiaYZPlane +=
      leftWing.getMass() * leftWing.getSpan(); // Approx for left wing
  totalInertiaYZPlane +=
      -rightWing.getMass() * rightWing.getSpan(); // Approx for right wing
  totalInertiaYZPlane += tail.getMass() * tail.getSpan(); // Tail contribution

  // Off-diagonal: XY Plane (Ixy)
  totalInertiaXYPlane = 0.0; // Initial contribution from fuselage
  totalInertiaXYPlane +=
      leftWing.getMass() * leftWing.getSpan(); // Approx for left wing
  totalInertiaXYPlane +=
      rightWing.getMass() * rightWing.getSpan(); // Approx for right wing
  totalInertiaXYPlane += tail.getMass() * tail.getSpan(); // Tail contribution

  // I found these formulas on the internet because I have no IDEA wtf any of
  // this is....
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

double Airplane::getTotalInertiaXZPlane() const { return totalInertiaXZPlane; }

double Airplane::getTotalInertiaYZPlane() const { return totalInertiaYZPlane; }

double Airplane::getTotalInertiaXYPlane() const { return totalInertiaXYPlane; }

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

void Airplane::setTotalInertiaXZPlane(double inertia) {
  totalInertiaXZPlane = inertia;
}

void Airplane::setTotalInertiaYZPlane(double inertia) {
  totalInertiaYZPlane = inertia;
}

void Airplane::setTotalInertiaXYPlane(double inertia) {
  totalInertiaXYPlane = inertia;
}

// Getter for inertia units
std::string Airplane::getInertiaUnits() const { return inertiaUnits; }

// Setter for inertia units
void Airplane::setInertiaUnits(const std::string &units) {
  inertiaUnits = units;
}

void Airplane::convertInertiaUnits() {
  const double slug_ft2_to_kg_m2 =
      1.35581795; // Conversion factor for SLUG*FT2 to KG*M2
  const double kg_m2_to_slug_ft2 =
      1.0 / slug_ft2_to_kg_m2; // Conversion factor for KG*M2 to SLUG*FT2

  if (inertiaUnits == "SLUG*FT2") {
    totalInertiaLongitudinal *= slug_ft2_to_kg_m2;
    totalInertiaTransverse *= slug_ft2_to_kg_m2;
    totalInertiaVertical *= slug_ft2_to_kg_m2;
    totalInertiaXZPlane *= slug_ft2_to_kg_m2;
    totalInertiaYZPlane *= slug_ft2_to_kg_m2;
    totalInertiaXYPlane *= slug_ft2_to_kg_m2;
    inertiaUnits = "KG*M2";
  } else if (inertiaUnits == "KG*M2") {
    totalInertiaLongitudinal *= kg_m2_to_slug_ft2;
    totalInertiaTransverse *= kg_m2_to_slug_ft2;
    totalInertiaVertical *= kg_m2_to_slug_ft2;
    totalInertiaXZPlane *= kg_m2_to_slug_ft2;
    totalInertiaYZPlane *= kg_m2_to_slug_ft2;
    totalInertiaXYPlane *= kg_m2_to_slug_ft2;
    inertiaUnits = "SLUG*FT2";
  }
}*/

// Constructor
MomentOfInertia::MomentOfInertia(double ixx, double iyy, double izz, double ixy,
                                 double ixz, double iyz,
                                 const std::string &unit)
    : Ixx(ixx), Iyy(iyy), Izz(izz), Ixy(ixy), Ixz(ixz), Iyz(iyz), unit(unit) {}

// Getters
double MomentOfInertia::getIxx() const { return Ixx; }
double MomentOfInertia::getIyy() const { return Iyy; }
double MomentOfInertia::getIzz() const { return Izz; }
double MomentOfInertia::getIxy() const { return Ixy; }
double MomentOfInertia::getIxz() const { return Ixz; }
double MomentOfInertia::getIyz() const { return Iyz; }
std::string MomentOfInertia::getUnit() const { return unit; }

// Setters
void MomentOfInertia::setIxx(double value) { Ixx = value; }
void MomentOfInertia::setIyy(double value) { Iyy = value; }
void MomentOfInertia::setIzz(double value) { Izz = value; }
void MomentOfInertia::setIxy(double value) { Ixy = value; }
void MomentOfInertia::setIxz(double value) { Ixz = value; }
void MomentOfInertia::setIyz(double value) { Iyz = value; }
void MomentOfInertia::setUnit(const std::string &newUnit) { unit = newUnit; }

void MomentOfInertia::convertInertiaUnits() {
  const double slug_ft2_to_kg_m2 =
      1.35581795; // Conversion factor for SLUG*FT2 to KG*M2
  const double kg_m2_to_slug_ft2 =
      1.0 / slug_ft2_to_kg_m2; // Conversion factor for KG*M2 to SLUG*FT2

  if (unit == "SLUG*FT2") {
    Ixx *= slug_ft2_to_kg_m2;
    Iyy *= slug_ft2_to_kg_m2;
    Izz *= slug_ft2_to_kg_m2;
    Ixy *= slug_ft2_to_kg_m2;
    Ixz *= slug_ft2_to_kg_m2;
    Iyz *= slug_ft2_to_kg_m2;
    unit = "KG*M2";
  } else if (unit == "KG*M2") {
    Ixx *= kg_m2_to_slug_ft2;
    Iyy *= kg_m2_to_slug_ft2;
    Izz *= kg_m2_to_slug_ft2;
    Ixy *= kg_m2_to_slug_ft2;
    Ixz *= kg_m2_to_slug_ft2;
    Iyz *= kg_m2_to_slug_ft2;
    unit = "SLUG*FT2";
  }
}

} // namespace MassBalance
