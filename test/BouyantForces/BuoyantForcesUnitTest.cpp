#include <iostream>
#include "BuoyantForces.hpp"

int main() {
    // Test 1: verify default state of buoyant forces
    BuoyantForces buoyantForces;
    if (!buoyantForces.isBuoyantForcesActive()) {
        std::cout << "Test 1 Passed: Default buoyant forces state is inactive.\n";
    } else {
        std::cerr << "Test 1 Failed: Default buoyant forces state is not inactive.\n";
    }

    // Test 2: set and verify buoyant forces state
    buoyantForces.setHasBuoyantForces(true);
    if (buoyantForces.isBuoyantForcesActive()) {
        std::cout << "Test 2 Passed: Buoyant forces state correctly set to active.\n";
    } else {
        std::cerr << "Test 2 Failed: Buoyant forces state not correctly set to active.\n";
    }

    // Test 3: set and verify gas cell
    GasCell gasCell;
    buoyantForces.setGasCell(gasCell);
    if (&buoyantForces.getGasCell() == &gasCell) { // compare mem address
        std::cout << "Test 3 Passed: GasCell correctly set and retrieved.\n";
    } else {
        std::cerr << "Test 3 Failed: GasCell not correctly set or retrieved.\n";
    }

    return 0;
}

