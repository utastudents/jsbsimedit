
#include <MassBalance/Emptymass.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cmath>

namespace MassBalance {

TEST_CASE("testing EmptyMass unit conversion") {
    MassBalance::EmptyMass emptyMass(100.0f, "LBS");
    const float tolerance = 0.01f; // Define a small tolerance for floating-point comparison

    SECTION("Convert from pounds to kilograms") {
        emptyMass.convertUnits();
        REQUIRE(std::fabs(emptyMass.getEmptyMass() - 45.3592f) < tolerance);
        REQUIRE(emptyMass.getUnits() == "KGS");
    }

    SECTION("Convert from kilograms to pounds") {
        emptyMass.setEmptyMass(45.3592f);
        emptyMass.setUnits("KGS");
        emptyMass.convertUnits();
        REQUIRE(std::fabs(emptyMass.getEmptyMass() - 100.0f) < tolerance);
        REQUIRE(emptyMass.getUnits() == "LBS");
    }
}

} // namespace MassBalance
