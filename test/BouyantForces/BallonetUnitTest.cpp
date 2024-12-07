#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <BuoyantForces/Ballonet.hpp>

// testing ballonet constructor
TEST_CASE("Ballonet Constructor with GasType") {
    Ballonet b("TestBallonet", Component::GasType::AIR);

    // initialization of blowerValue and blowerUnits
    REQUIRE(b.getBlowerValue() == 0); // blowerValue is initialized to 0
    REQUIRE(b.getBlowerUnit() == Component::Unit::FT3_SEC); //blowerUnits is FT3_SEC
}

TEST_CASE("Ballonet Constructor without GasType") {
    Ballonet b("TestBallonet");

    // initialization of blowerValue and blowerUnits
    REQUIRE(b.getBlowerValue() == 0); //blowerValue is initialized to 0
    REQUIRE(b.getBlowerUnit() == Component::Unit::FT3_SEC); //blowerUnits is FT3_SEC
}
