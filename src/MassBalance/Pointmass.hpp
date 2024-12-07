#pragma once
#include <string>
namespace MassBalance {

class PointMass {
private:
  std::string name;
  std::string locationUnit;
  std::string weightUnit;
  double x;
  double y;
  double z;
  double weight;

public:
  // Constructors
  PointMass();
  PointMass(const std::string &newName, const std::string &locUnit,
            const std::string &wtUnit, double newX, double newY, double newZ,
            double newWeight);

  // Getters
  std::string getName() const;
  std::string getLocationUnit() const;
  std::string getWeightUnit() const;
  double getX() const;
  double getY() const;
  double getZ() const;
  double getWeight() const;

  // Setters
  void setName(const std::string &newName);
  void setLocationUnit(const std::string &locUnit);
  void setWeightUnit(const std::string &wtUnit);
  void setX(double newX);
  void setY(double newY);
  void setZ(double newZ);
  void setWeight(double newWeight);
  void convertLengthUnits();
};
} // namespace MassBalance