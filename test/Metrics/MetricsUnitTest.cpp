#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include <gtkmm.h> 
#include <memory>
#include "MetricsSubsystem.hpp" 

/*"wingarea", {"FT2", "M2"}},
    {"wingspan", {"FT", "M"}},
    {"wing_incidence", {"FT", "M"}},
    {"chord", {"DEG"}},
    {"htailarea", {"FT2", "M2"}},
    {"htailarm", {"FT", "M"}},
    {"vtailarea", {"FT2", "M2"}},
    {"vtailarm", {"FT", "M"}},
    {"location", {"IN", "FT", "M"}}}*/

TEST_CASE("Verify Metrics Interface Opens and Stays Open")
{
   MetricsSubsystem metrics;

   //simulate opening the Metrics tab
   metrics.Create();

   //Check initial data units
  REQUIRE(metrics.data_units.size() == 8); //8 data units fields
  REQUIRE(metrics.vertex_data_units.size() == 3); //3 vertex unit fields
}

TEST_CASE("Verify eight data unit windows are displayed")
{
    MetricsSubsystem metrics;

    //simulate opening the Metrics tab
    metrics.Create();
    
  //validate specific data units
  REQUIRE(metrics.data_units["wingarea"]->get_its_unit()->get_unit_bank().size() == 2); //FT2, M2
  REQUIRE(metrics.data_units["wingarea"]->get_its_unit()->get_current_unit() == "");
  
  REQUIRE(metrics.data_units["wingspan"]->get_its_unit()->get_unit_bank().size() == 2); //FT, M
  REQUIRE(metrics.data_units["wingspan"]->get_its_unit()->get_current_unit() == "");

  REQUIRE(metrics.data_units["wing_incidence"]->get_its_unit()->get_unit_bank().size() == 2); //FT, M
  REQUIRE(metrics.data_units["wing_incidence"]->get_its_unit()->get_current_unit() == "");

  REQUIRE(metrics.data_units["chord"]->get_its_unit()->get_unit_bank().size() == 1); //DEG
  REQUIRE(metrics.data_units["chord"]->get_its_unit()->get_current_unit() == "");

  REQUIRE(metrics.data_units["htailarea"]->get_its_unit()->get_unit_bank().size() == 2); //FT2, M2
  REQUIRE(metrics.data_units["htailarea"]->get_its_unit()->get_current_unit() == "");

  REQUIRE(metrics.data_units["htailarm"]->get_its_unit()->get_unit_bank().size() == 2); //FT, M
  REQUIRE(metrics.data_units["htailarm"]->get_its_unit()->get_current_unit() == "");

  REQUIRE(metrics.data_units["vtailarea"]->get_its_unit()->get_unit_bank().size() == 2); //FT2, M2
  REQUIRE(metrics.data_units["vtailarea"]->get_its_unit()->get_current_unit() == "");

  REQUIRE(metrics.data_units["vtailarm"]->get_its_unit()->get_unit_bank().size() == 2); //FT, M
  REQUIRE(metrics.data_units["vtailarm"]->get_its_unit()->get_current_unit() == "");
}

TEST_CASE("Verify three vertex data units are displayed")
{
    MetricsSubsystem metrics;

    //simulate opening the Metrics tab
    metrics.Create();
    
  //validate speficic vertex data units
  REQUIRE(metrics.vertex_data_units["Eye Point"]->get_its_unit()->get_unit_bank().size() == 3); //IN, FT, M
  REQUIRE(metrics.vertex_data_units["Eye Point"]->get_its_unit()->get_current_unit() == "");
   
  REQUIRE(metrics.vertex_data_units["Visual Reference Point"]->get_its_unit()->get_unit_bank().size() == 3); //IN, FT, M
  REQUIRE(metrics.vertex_data_units["Visual Reference Point"]->get_its_unit()->get_current_unit() == "");
   
  REQUIRE(metrics.vertex_data_units["Aerodynamic Reference Point"]->get_its_unit()->get_unit_bank().size() == 3); //IN, FT, M
  REQUIRE(metrics.vertex_data_units["Aerodynamic Reference Point"]->get_its_unit()->get_current_unit() == "");
}
