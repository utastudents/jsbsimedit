#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <BuoyantForces/GasCell.hpp>

TEST_CASE("GasCell Constructor") {
    GasCell gasCell;

    // this will check the ballonets initail state makeing sure it has 0 ballonets
    REQUIRE(gasCell.getBallonetCount() == 0);
    REQUIRE(gasCell.getBallonets().empty());
}



TEST_CASE("Add Ballonet to GasCell") {
    GasCell gasCell;
    //testing if ballonets can be added properly to gas cell
    Ballonet ballonet1("Ballonet1", Component::GasType::AIR);
    Ballonet ballonet2("Ballonet2", Component::GasType::HELIUM);

    
    gasCell.addBallonet(ballonet1);
    gasCell.addBallonet(ballonet2);

    // checking if added  correctly
    REQUIRE(gasCell.getBallonetCount() == 2);
    REQUIRE(gasCell.getBallonets().size() == 2);
    REQUIRE(gasCell.getBallonet(0).getName() == "Ballonet1");
    REQUIRE(gasCell.getBallonet(1).getName() == "Ballonet2");
}

TEST_CASE("Remove Last Ballonet from GasCell") {
    GasCell gasCell;
    //testing the  removal of ballonets
    Ballonet ballonet1("Ballonet1", Component::GasType::AIR);
    Ballonet ballonet2("Ballonet2", Component::GasType::HELIUM);

    //adding ballonets
    gasCell.addBallonet(ballonet1);
    gasCell.addBallonet(ballonet2);

    // Removing last added ballonet
    gasCell.removeLastBallonet();

    // check if deleted
    REQUIRE(gasCell.getBallonetCount() == 1);
    REQUIRE(gasCell.getBallonets().size() == 1);
    REQUIRE(gasCell.getBallonet(0).getName() == "Ballonet1");
}


