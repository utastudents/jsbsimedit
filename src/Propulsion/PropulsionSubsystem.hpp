#pragma once
#include "inc/Subsystem.hpp"
#include "gtkmm.h"
#include "PropulsionManager.hpp"



class PropulsionSubsystem : public Subsystem {
  public:
    PropulsionSubsystem();
    void Create(); 
    void on_button_clicked();
    
    PropulsionManager m_PropManager;
};
