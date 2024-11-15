#pragma once

#include "gtkmm.h"
#include "inc/Subsystem.hpp"
#include "Systems/FlightControlDemo.hpp"

// This class is just an isolation between the 
// main system and the flight control subsystem.
// It was easier to create some code that bridged
// the differences than change code inside the
// subsystem
class FlightControlsSubsystem : public Subsystem
{
  public:
    FlightControlsSubsystem();
    void Create(); 
  private:
    DragDrop::FlightControlDemo *m_demo;
};
