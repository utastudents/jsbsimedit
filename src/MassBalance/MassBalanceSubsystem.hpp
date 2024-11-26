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

private:
  MassBalance::Location m_Location;
  MassBalance::EmptyMass m_Emptymass;
  MassBalance::Fuselage m_fuselage; // mass, length, radius
  MassBalance::Wing m_leftWing;     // mass, span, chord
  MassBalance::Wing m_rightWing;    // mass, span, chord
  MassBalance::Tail m_tail;         // mass, span, chord
};
