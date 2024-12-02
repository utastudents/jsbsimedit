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
