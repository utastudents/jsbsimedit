#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include <gtkmm.h> 
#include <memory>
#include "MetricsSubsystem.hpp" 

TEST_CASE("MetricsSubsystem Initialization")
{
   MetricsSubsystem metrics;

   //Check initial data units
  REQUIRE(metrics.data_units.size() == 8); //8 data units fields
  REQUIRE(metrics.vertex_data_units.size() == 3); //3 vertex unit fields

  //validate specific data units
  REQUIRE(metrics.data_units["wingarea"]->get_its_unit()->get_unit_bank().size() == 2); //FT2, M2
  REQUIRE(metrics.data_units["wingarea"]->get_its_unit()->get_current_unit() == "");

  REQUIRE(metrics.vertex_data_units["Aerodynamic Reference Point"]->get_its_unit()->get_unit_bank().size() == 3); //IN, FT, M
}
