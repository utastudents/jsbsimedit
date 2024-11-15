#include <iostream>
#include <assert.h>

#include "FlightControlsSubsystem.hpp"
#include "FlightControlDemo.hpp"

FlightControlsSubsystem::FlightControlsSubsystem()
{
    m_Name = "FlightControls";
    std::cout << "In FlightControlsSubsystem contructor" << std::endl; 
}

void FlightControlsSubsystem::Create()
{
  std::cout << "in FlightControls::Create" << std::endl;
  m_demo = new DragDrop::FlightControlDemo(nullptr);
  assert(m_demo);
  //m_Grid = 
}
