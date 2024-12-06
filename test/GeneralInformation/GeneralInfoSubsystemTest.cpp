#include <catch2/catch_test_macros.hpp>
#include <GeneralInformation/GeneralInformationSubsystem.hpp>

TEST_CASE("Verify General Information Subsystem Initializes") {
    GeneralInformationSubsystem subsystem;

    REQUIRE_NOTHROW(subsystem.Create());
    REQUIRE(subsystem.getAircraftName().empty()); // Default state
    REQUIRE(subsystem.getAuthor().empty());       // Default state
}