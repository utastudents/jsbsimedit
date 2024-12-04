#pragma once

#include <string>

namespace MassBalance {

class EmptyMass {
private:
  float emptyMass;   // Mass value
  std::string units; // Units of measurement

public:
  // Constructor
  EmptyMass(float massValue = 0.0f, const std::string &unitMeasure = "lbs");

  // Setters
  void setEmptyMass(float massValue);
  void setUnits(const std::string &unitMeasure);

  // Getters
  float getEmptyMass() const;
  std::string getUnits() const;

  void convertUnits();
};

} // namespace MassBalance