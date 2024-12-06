#include <catch2/catch_test_macros.hpp>
#include <GeneralInformation/GeneralInformationSubsystem.hpp>
#include <XML/XMLDoc.hpp>

TEST_CASE("Verify General Information XML Saving") {
    GeneralInformationSubsystem subsystem;

    subsystem.setAircraftName("F-16");
    subsystem.setAuthor("John Doe");
    subsystem.setEmail("john.doe@example.com");
    subsystem.setReleaseLevel("ALPHA");

    SECTION("Save valid XML") {
        REQUIRE_NOTHROW(subsystem.SaveToXML("test_data/output.xml"));

        JSBEdit::XMLDoc xmlDoc;
        xmlDoc.LoadFileAndParse("test_data/output.xml");

        REQUIRE(xmlDoc.GetNode("/fdm_config/GeneralInfo/AircraftName").get_text() == "F-16");
        REQUIRE(xmlDoc.GetNode("/fdm_config/GeneralInfo/Author").get_text() == "John Doe");
        REQUIRE(xmlDoc.GetNode("/fdm_config/GeneralInfo/Email").get_text() == "john.doe@example.com");
    }

    SECTION("Save to invalid path") {
        REQUIRE_THROWS_AS(subsystem.SaveToXML(""), std::invalid_argument);
    }
}