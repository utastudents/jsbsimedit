#define BOOST_TEST_MODULE EmptyMassTest
#include <boost/test/included/unit_test.hpp>
#include "Emptymass.hpp"

BOOST_AUTO_TEST_SUITE(EmptyMassConversionTests)

BOOST_AUTO_TEST_CASE(ConvertFromLbsToKgs) {
    // Create an EmptyMass object with 100 lbs
    MassBalance::EmptyMass mass(100.0, "lbs");

    // Convert to kilograms
    mass.convertUnits();

    // Check the mass in kilograms
    BOOST_CHECK_CLOSE(mass.getEmptyMass(), 45.3592, 0.0001); // 100 lbs = 45.3592 kg
    BOOST_CHECK_EQUAL(mass.getUnits(), "kgs");
}

BOOST_AUTO_TEST_CASE(ConvertFromKgsToLbs) {
    // Create an EmptyMass object with 45.3592 kgs
    MassBalance::EmptyMass mass(45.3592, "kgs");

    // Convert to pounds
    mass.convertUnits();

    // Check the mass in pounds
    BOOST_CHECK_CLOSE(mass.getEmptyMass(), 100.0, 0.0001); // 45.3592 kg = 100 lbs
    BOOST_CHECK_EQUAL(mass.getUnits(), "lbs");
}

BOOST_AUTO_TEST_SUITE_END()





