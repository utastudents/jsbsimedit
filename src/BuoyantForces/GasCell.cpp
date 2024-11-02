#include "Component.hpp"

// GasCell constructor
GasCell::GasCell(double v, double t, double p, double m) : Component() {
    volume = v;
    temperature = t;
    pressure = p;
    mass = m;
}

GasCell::~GasCell() {
    // Destructor definition
}