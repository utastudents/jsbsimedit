#pragma once
#include "Emptymass.hpp"
#include "Location.hpp"
#include <string>

namespace MassBalance {

class PointMass {
private:
  std::string name;
  Location newLoc;
  EmptyMass newMass;

public:
  // Constructor
  PointMass(const std::string &name, const Location &loc,
            const EmptyMass &mass);

  // Getters
  std::string getName() const;
  Location getLocation() const;
  EmptyMass getMass() const;

  // Setters
  void setName(const std::string &newName);
  void setLocation(const Location &loc);
  void setMass(const EmptyMass &mass);
};
} // namespace MassBalance