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

// Test other setters and getters
 
TEST_CASE("Testing GasType to String Conversion") {
    GasCell gasCell;

    REQUIRE();
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