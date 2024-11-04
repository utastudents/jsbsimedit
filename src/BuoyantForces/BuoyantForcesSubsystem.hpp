#pragma once
#include "../inc/Subsystem.hpp"
//#include "gtkmm.h"
class BuoyantForcesSubsystem : public Subsystem
{
  public:
    std::string m_name;
    BuoyantForcesSubsystem(std::string N);
    void Create();
};
