#include "BuoyantForces.hpp"

BuoyantForces::BuoyantForces() {
    hasBuoyantForces = false;
}

void BuoyantForces::setHasBuoyantForces(bool byfActive) {
    hasBuoyantForces = byfActive;
    // std::cout << "   [in buoyant forces class] bool has changed to " << ((hasBuoyantForces) ? "TRUE" : "FALSE") << std::endl;
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