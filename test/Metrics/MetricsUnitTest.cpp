#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include <Metrics/MetricsSubsystem.hpp>

TEST_CASE("Metrics update_text (string -> double)")
{
  REQUIRE(1.0 == MetricsSubsystem::update_text("1.0"));
  REQUIRE(1.0 == MetricsSubsystem::update_text("1.0.0"));

  REQUIRE(0.0 == MetricsSubsystem::update_text("foo"));
  REQUIRE(0.0 == MetricsSubsystem::update_text("//1.0"));
}

// TEST_CASE("Verify three vertex data units are displayed")
// {
//     MetricsSubsystem metrics;

//     //simulate opening the Metrics tab
//     metrics.Create();
    
//   //validate speficic vertex data units
//   REQUIRE(metrics.vertex_data_units["Eye Point"]->get_its_unit()->get_unit_bank().size() == 3); //IN, FT, M
//   REQUIRE(metrics.vertex_data_units["Eye Point"]->get_its_unit()->get_current_unit() == "");
   
//   REQUIRE(metrics.vertex_data_units["Visual Reference Point"]->get_its_unit()->get_unit_bank().size() == 3); //IN, FT, M
//   REQUIRE(metrics.vertex_data_units["Visual Reference Point"]->get_its_unit()->get_current_unit() == "");
   
//   REQUIRE(metrics.vertex_data_units["Aerodynamic Reference Point"]->get_its_unit()->get_unit_bank().size() == 3); //IN, FT, M
//   REQUIRE(metrics.vertex_data_units["Aerodynamic Reference Point"]->get_its_unit()->get_current_unit() == "");
// }