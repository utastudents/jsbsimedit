#pragma once

#include <string>

namespace MassBalance {

class Location {
private:
  double x, y, z;    // Coordinates
  std::string units; // Units of measurement

public:
  // Constructor
  Location(double x = 0.0, double y = 0.0, double z = 0.0,
           const std::string &units = "in");

  // Setters
  void setLocation(double newX, double newY, double newZ);
  void setUnits(const std::string &unitMeasure);
  void setX(double newX);
  void setY(double newY);
  void setZ(double newZ);

  // Getters
  double getX() const;
  double getY() const;
  double getZ() const;
  std::string getUnits() const;
  void convertLengthUnits();
};

} // namespace MassBalance
