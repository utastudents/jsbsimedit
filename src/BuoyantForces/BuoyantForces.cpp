#include "BuoyantForces.hpp"

BuoyantForces::BuoyantForces() {
    hasBuoyantForces = false;
}

void BuoyantForces::setHasBuoyantForces(bool byfActive) {
    hasBuoyantForces = byfActive;
}

void BuoyantForces::setGasCell(GasCell newGasCell){
    gasCell = newGasCell;
}

bool BuoyantForces::isBuoyantForcesActive() {
    return hasBuoyantForces;
}

GasCell BuoyantForces::getGasCell() {
    return gasCell;
}
