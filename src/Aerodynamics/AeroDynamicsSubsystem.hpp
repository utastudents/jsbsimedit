#pragma once
#include "inc/Subsystem.hpp"
#include "gtkmm.h"
class AeroDynamicsSubsystem : public Subsystem
{
  public:
    std::string m_name;
    AeroDynamicsSubsystem(std::string N);
    void Create(); 
};
