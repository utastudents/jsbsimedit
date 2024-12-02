#pragma once
#include "Emptymass.hpp"
#include "Location.hpp"
#include "MomentOfInertia.hpp"
#include "gtkmm.h"
#include "inc/Subsystem.hpp"

class MassBalanceSubsystem : public Subsystem {
public:
  MassBalanceSubsystem();
  void Create();
  void on_button_pressed();

private:
  MassBalance::Location m_Location;
  MassBalance::EmptyMass m_Emptymass;
  MassBalance::MomentOfInertia m_airplane;
};
