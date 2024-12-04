#define BOOST_TEST_DYN_LINK  // This is important for dynamic linking
#define BOOST_TEST_MODULE MomentOfInertiaTest
#include <boost/test/unit_test.hpp>
#include "MomentOfInertia.hpp"

namespace MassBalance {
    BOOST_AUTO_TEST_SUITE(MomentOfInertiaTest)

    // Test conversion from SLUG*FT2 to KG*M2
    BOOST_AUTO_TEST_CASE(testConvertFromSlugFt2ToKgM2)
    {
        // Create a MomentOfInertia object with some initial values in SLUG*FT2
        MomentOfInertia moi(10.0, 20.0, 30.0, 5.0, 2.0, 1.0, false, "SLUG*FT2");

        // Save the initial values
        double initialIxx = moi.getIxx();
        double initialIyy = moi.getIyy();
        double initialIzz = moi.getIzz();
        double initialIxy = moi.getIxy();
        double initialIxz = moi.getIxz();
        double initialIyz = moi.getIyz();
        std::string initialUnit = moi.getUnit();

        // Perform the conversion
        moi.convertInertiaUnits();

        // Check that the unit has been converted to KG*M2
        BOOST_CHECK_EQUAL(moi.getUnit(), "KG*M2");

        // Verify the values are converted correctly
        const double conversionFactor = 1.35581795;
        BOOST_CHECK_CLOSE(moi.getIxx(), initialIxx * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIyy(), initialIyy * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIzz(), initialIzz * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIxy(), initialIxy * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIxz(), initialIxz * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIyz(), initialIyz * conversionFactor, 0.0001);
    }

    // Test conversion from KG*M2 to SLUG*FT2
    BOOST_AUTO_TEST_CASE(testConvertFromKgM2ToSlugFt2)
    {
        // Create a MomentOfInertia object with some initial values in KG*M2
        MomentOfInertia moi(10.0, 20.0, 30.0, 5.0, 2.0, 1.0, false, "KG*M2");

        // Save the initial values
        double initialIxx = moi.getIxx();
        double initialIyy = moi.getIyy();
        double initialIzz = moi.getIzz();
        double initialIxy = moi.getIxy();
        double initialIxz = moi.getIxz();
        double initialIyz = moi.getIyz();
        std::string initialUnit = moi.getUnit();

        // Perform the conversion
        moi.convertInertiaUnits();

        // Check that the unit has been converted to SLUG*FT2
        BOOST_CHECK_EQUAL(moi.getUnit(), "SLUG*FT2");

        // Verify the values are converted correctly
        const double conversionFactor = 1.0 / 1.35581795;
        BOOST_CHECK_CLOSE(moi.getIxx(), initialIxx * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIyy(), initialIyy * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIzz(), initialIzz * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIxy(), initialIxy * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIxz(), initialIxz * conversionFactor, 0.0001);
        BOOST_CHECK_CLOSE(moi.getIyz(), initialIyz * conversionFactor, 0.0001);
    }

    BOOST_AUTO_TEST_SUITE_END()
}
