#pragma once
#include "inc/Subsystem.hpp"
#include "gtkmm.h"
#include "Emptymass.hpp"
#include "Location.hpp"




class MassBalanceSubsystem : public Subsystem {
  public:
    MassBalanceSubsystem();
    void Create(); 

  private:
    MassBalance::Location m_Location;
    MassBalance::EmptyMass m_Emptymass;

};

