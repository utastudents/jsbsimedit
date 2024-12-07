#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <BuoyantForces/Component.hpp>
#include <BuoyantForces/GasCell.hpp>
#include <BuoyantForces/Ballonet.hpp>

// Component is an abstract class
// Test using subclasses

TEST_CASE("Verifying Default States of Class Members") {
    GasCell gasCell;

    // Verifying getters
    REQUIRE(gasCell.getXLocation() == 0.0);
    REQUIRE(gasCell.getYLocation() == 0.0);
    REQUIRE(gasCell.getZLocation() == 0.0);
    REQUIRE(gasCell.getXDimension() == 0.0);
    REQUIRE(gasCell.getYDimension() == 0.0);
    REQUIRE(gasCell.getZDimension() == 0.0);
    REQUIRE(gasCell.getOverpressure() == 0.0);
    REQUIRE(gasCell.getValveCoefficient() == 0.0);
    REQUIRE(gasCell.getInitialFullness() == 1.0);
    REQUIRE(gasCell.getGasType() == Component::GasType::AIR);
    REQUIRE(gasCell.getLocationUnit() == Component::Unit::M);
    REQUIRE(gasCell.getDimensionsUnit() == Component::Unit::M);
    REQUIRE(gasCell.getDimensionsShape() == Component::Unit::WIDTH);
    REQUIRE(gasCell.getPressureUnit() == Component::Unit::PA);
    REQUIRE(gasCell.getValveCoefficientUnit() == Component::Unit::FT4_SEC_SLUG);
}

TEST_CASE("Set and Verify X Location") {
    GasCell gasCell;

    gasCell.setXLocation(12.34);
    REQUIRE(gasCell.getXLocation() == 12.34);
}

TEST_CASE("Set and Verify Y Location") {
    GasCell gasCell;

    gasCell.setYLocation(56.78);
    REQUIRE(gasCell.getXLocation() == 56.78);
}

TEST_CASE("Set and Verify Z Location") {
    GasCell gasCell;

    gasCell.setZLocation(90.12);
    REQUIRE(gasCell.getXLocation() == 90.12);
}

TEST_CASE("Set and Verify X Dimension") {
    GasCell gasCell;

    gasCell.setXLocation(101.99);
    REQUIRE(gasCell.getXLocation() == 101.99);
}

TEST_CASE("Set and Verify Y Dimension") {
    GasCell gasCell;

    gasCell.setXLocation(-123.45);
    REQUIRE(gasCell.getXLocation() == -123.45);
}

TEST_CASE("Set and Verify Z Dimension") {
    GasCell gasCell;

    gasCell.setXLocation(0.123);
    REQUIRE(gasCell.getXLocation() == 0.123);
}

// Add test cases for rest of class members

TEST_CASE("Set and Verify Name") {
    GasCell gasCell;

    gasCell.setName("Test Gas Cell");
    REQUIRE(gasCell.getName() == "Test Gas Cell");
}
 
TEST_CASE("Testing GasType to String Conversion") {
    GasCell gasCell;

    REQUIRE(gasCell.gasTypeToString(Component::GasType::AIR) == "AIR");
    REQUIRE(gasCell.gasTypeToString(Component::GasType::HELIUM) == "HELIUM");
    REQUIRE(gasCell.gasTypeToString(Component::GasType::HYDROGEN) == "HYDROGEN");
}

TEST_CASE("Testing Unit to String Conversion") {
    GasCell gasCell;

    REQUIRE(gasCell.unitToString(Component::Unit::WIDTH) == "width");
    REQUIRE(gasCell.unitToString(Component::Unit::RADIUS) == "radius");

    REQUIRE(gasCell.unitToString(Component::Unit::PA) == "PA");
    REQUIRE(gasCell.unitToString(Component::Unit::PSI) == "PSI");
    
    REQUIRE(gasCell.unitToString(Component::Unit::M) == "M");
    REQUIRE(gasCell.unitToString(Component::Unit::IN) == "IN");
    
    REQUIRE(gasCell.unitToString(Component::Unit::FT4_SEC_SLUG) == "FT4*SEC/SLUG");
    REQUIRE(gasCell.unitToString(Component::Unit::M4_SEC_KG) == "M4*SEC/KG");
    
    REQUIRE(gasCell.unitToString(Component::Unit::LBS_FT_SEC) == "lbs ft / sec");
    REQUIRE(gasCell.unitToString(Component::Unit::LB_FT_SEC_R) == "lb ft / (sec R)");
    
    REQUIRE(gasCell.unitToString(Component::Unit::FT3_SEC) == "ft^3 / sec");
}

TEST_CASE("Set and Verify Fullness") {
    GasCell gasCell;

    gasCell.setInitialFullness(0.75);  // initializing fullness
    REQUIRE(gasCell.getInitialFullness() == 0.75);  //checking if true
}
TEST_CASE("Set and Verify Max Pressure") {
    GasCell gasCell;

    gasCell.setMaxPressure(1000.0);  //initializing maxpressure
    REQUIRE(gasCell.getMaxPressure() == 1000.0);  // checking  if true
}

TEST_CASE("Set and Verify GasType") {
    GasCell gasCell;

    gasCell.setGasType(Component::GasType::HELIUM);  //initializing to Helium
    REQUIRE(gasCell.getGasType() == Component::GasType::HELIUM);  //checking if true
}
