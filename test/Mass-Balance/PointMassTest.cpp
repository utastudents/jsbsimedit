
#include <MassBalance/Pointmass.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cmath>

namespace MassBalance {

TEST_CASE("PointMass length unit conversion") {
    const double tolerance = 1e-6; // Define a tolerance for floating-point comparisons

    // Create a PointMass object with location in inches
    MassBalance::PointMass pointMass("TestMass", "in", "LBS", 10.0, 20.0, 30.0, 100.0);

    SECTION("Convert from inches to centimeters") {
        pointMass.convertLengthUnits();
        REQUIRE(std::fabs(pointMass.getX() - 25.4) < tolerance);
        REQUIRE(std::fabs(pointMass.getY() - 50.8) < tolerance);
        REQUIRE(std::fabs(pointMass.getZ() - 76.2) < tolerance);
        REQUIRE(pointMass.getLocationUnit() == "cm");
    }

    SECTION("Convert from centimeters to inches") {
        pointMass.convertLengthUnits(); // Convert to centimeters first
        pointMass.convertLengthUnits(); // Convert back to inches
        REQUIRE(std::fabs(pointMass.getX() - 10.0) < tolerance);
        REQUIRE(std::fabs(pointMass.getY() - 20.0) < tolerance);
        REQUIRE(std::fabs(pointMass.getZ() - 30.0) < tolerance);
        REQUIRE(pointMass.getLocationUnit() == "in");
    }
}

} // namespace MassBalance
