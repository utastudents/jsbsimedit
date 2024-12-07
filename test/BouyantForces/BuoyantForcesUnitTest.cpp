#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <BuoyantForces/BuoyantForces.hpp>

TEST_CASE("Verify BuoyantForces Default State") {
    BuoyantForces buoyantForces;

    REQUIRE(buoyantForces.isBuoyantForcesActive() == false);
}

TEST_CASE("Set and Verify Buoyant Forces State") {
    BuoyantForces buoyantForces;

    buoyantForces.setHasBuoyantForces(true);
    REQUIRE(buoyantForces.isBuoyantForcesActive() == true);
}

TEST_CASE("Set and Verify Gas Cell") {
    BuoyantForces buoyantForces;
    GasCell gasCell;

    buoyantForces.setGasCell(gasCell);
    REQUIRE(buoyantForces.getGasCell() == gasCell);  
}
