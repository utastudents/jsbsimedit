#pragma once
#include "inc/Subsystem.hpp"
#include "gtkmm.h"
#include "PropulsionManager.hpp"



class PropulsionSubsystem : public Subsystem {
  public:
    PropulsionSubsystem();
    void Create(); 

    PropulsionManager m_PropManager;
};
