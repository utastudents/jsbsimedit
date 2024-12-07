
#include <MassBalance/MomentOfInertia.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cmath>

namespace MassBalance {

TEST_CASE("MomentOfInertia unit conversion") {
    const double tolerance = 1e-6; // Define a tolerance for floating-point comparisons

    // Create a MomentOfInertia object in SLUG*FT2
    MassBalance::MomentOfInertia moment(10.0, 20.0, 30.0, 5.0, 15.0, 25.0, false, "SLUG*FT2");

    SECTION("Convert from SLUG*FT2 to KG*M2") {
        moment.convertInertiaUnits();
        REQUIRE(std::fabs(moment.getIxx() - 13.5581795) < tolerance);
        REQUIRE(std::fabs(moment.getIyy() - 27.116359) < tolerance);
        REQUIRE(std::fabs(moment.getIzz() - 40.6745385) < tolerance);
        REQUIRE(std::fabs(moment.getIxy() - 6.77908975) < tolerance);
        REQUIRE(std::fabs(moment.getIxz() - 20.33726925) < tolerance);
        REQUIRE(std::fabs(moment.getIyz() - 33.89544875) < tolerance);
        REQUIRE(moment.getUnit() == "KG*M2");
    }

    SECTION("Convert from KG*M2 to SLUG*FT2") {
        moment.convertInertiaUnits(); // Convert to KG*M2 first
        moment.convertInertiaUnits(); // Convert back to SLUG*FT2
        REQUIRE(std::fabs(moment.getIxx() - 10.0) < tolerance);
        REQUIRE(std::fabs(moment.getIyy() - 20.0) < tolerance);
        REQUIRE(std::fabs(moment.getIzz() - 30.0) < tolerance);
        REQUIRE(std::fabs(moment.getIxy() - 5.0) < tolerance);
        REQUIRE(std::fabs(moment.getIxz() - 15.0) < tolerance);
        REQUIRE(std::fabs(moment.getIyz() - 25.0) < tolerance);
        REQUIRE(moment.getUnit() == "SLUG*FT2");
    }
}

} // namespace MassBalance
