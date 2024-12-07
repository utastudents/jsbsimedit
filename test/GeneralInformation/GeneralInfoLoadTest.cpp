// #include <catch2/catch_test_macros.hpp>
// #include <GeneralInformation/GeneralInformationSubsystem.hpp>
// #include <XML/XMLDoc.hpp>

// TEST_CASE("Verify General Information XML Loading") {
//     GeneralInformationSubsystem subsystem;

//     SECTION("Load valid XML file") {
//         REQUIRE_NOTHROW(subsystem.LoadFromXML("test_data/sample.xml"));
//         REQUIRE(subsystem.getAircraftName() == "Boeing 747");
//         REQUIRE(subsystem.getAuthor() == "Jane Doe");
//         REQUIRE(subsystem.getEmail() == "jane.doe@example.com");
//         REQUIRE(subsystem.getReleaseLevel() == "BETA");
//     }

//     SECTION("Load invalid XML file") {
//         REQUIRE_THROWS_AS(subsystem.LoadFromXML("invalid.xml"), std::runtime_error);
//     }
// }
