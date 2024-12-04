#define BOOST_TEST_MODULE LocationTest
#include <boost/test/included/unit_test.hpp>
#include "Location.hpp"

namespace MassBalance {
    
// Test fixture
struct LocationFixture {
    Location loc_inch;
    Location loc_cm;

    LocationFixture()
        : loc_inch(10.0, 20.0, 30.0, "in"),  // Initial values in inches
          loc_cm(25.4, 50.8, 76.2, "cm") {}  // Initial values in centimeters
};

// Test converting inches to centimeters
BOOST_FIXTURE_TEST_CASE(ConvertInchesToCentimeters, LocationFixture)
{
    // Before conversion, check initial values
    BOOST_CHECK_EQUAL(loc_inch.getUnits(), "in");
    BOOST_CHECK_EQUAL(loc_inch.getX(), 10.0);
    BOOST_CHECK_EQUAL(loc_inch.getY(), 20.0);
    BOOST_CHECK_EQUAL(loc_inch.getZ(), 30.0);

    // Perform conversion
    loc_inch.convertLengthUnits();

    // After conversion, check the new values
    BOOST_CHECK_EQUAL(loc_inch.getUnits(), "cm");
    BOOST_CHECK_CLOSE(loc_inch.getX(), 25.4, 0.01);  // 10 inches to cm
    BOOST_CHECK_CLOSE(loc_inch.getY(), 50.8, 0.01);  // 20 inches to cm
    BOOST_CHECK_CLOSE(loc_inch.getZ(), 76.2, 0.01);  // 30 inches to cm
}

// Test converting centimeters to inches
BOOST_FIXTURE_TEST_CASE(ConvertCentimetersToInches, LocationFixture)
{
    // Before conversion, check initial values
    BOOST_CHECK_EQUAL(loc_cm.getUnits(), "cm");
    BOOST_CHECK_EQUAL(loc_cm.getX(), 25.4);
    BOOST_CHECK_EQUAL(loc_cm.getY(), 50.8);
    BOOST_CHECK_EQUAL(loc_cm.getZ(), 76.2);

    // Perform conversion
    loc_cm.convertLengthUnits();

    // After conversion, check the new values
    BOOST_CHECK_EQUAL(loc_cm.getUnits(), "in");
    BOOST_CHECK_CLOSE(loc_cm.getX(), 10.0, 0.01);  // 25.4 cm to inches
    BOOST_CHECK_CLOSE(loc_cm.getY(), 20.0, 0.01);  // 50.8 cm to inches
    BOOST_CHECK_CLOSE(loc_cm.getZ(), 30.0, 0.01);  // 76.2 cm to inches
}

} 
