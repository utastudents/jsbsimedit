#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <BuoyantForces/Component.hpp>
#include <BuoyantForces/GasCell.hpp>
#include <BuoyantForces/Ballonet.hpp>

// Component is an abstract class
// Test using subclasses

TEST_CASE("Testing") {
    GasCell gasCell;
    Ballonet ballonet;

    // REQUIRE();
}