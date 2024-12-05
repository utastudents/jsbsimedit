#include <MassBalance/Location.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cmath>

namespace MassBalance {

TEST_CASE("testing conversion") {
  MassBalance::Location location(10.0, 20.0, 30.0, "in");
  const double tolerance =
      0.01; // Define a small tolerance for floating-point comparison

  SECTION("Convert from inches to centimeters") {
    location.convertLengthUnits();
    REQUIRE(std::fabs(location.getX() - 25.4) < tolerance);
    REQUIRE(std::fabs(location.getY() - 50.8) < tolerance);
    REQUIRE(std::fabs(location.getZ() - 76.2) < tolerance);
    REQUIRE(location.getUnits() == "cm");
  }

  SECTION("Convert from centimeters to inches") {
    location.setLocation(25.4, 50.8, 76.2);
    location.setUnits("cm");
    location.convertLengthUnits();
    REQUIRE(std::fabs(location.getX() - 10.0) < tolerance);
    REQUIRE(std::fabs(location.getY() - 20.0) < tolerance);
    REQUIRE(std::fabs(location.getZ() - 30.0) < tolerance);
    REQUIRE(location.getUnits() == "in");
  }
}

} // namespace MassBalance
