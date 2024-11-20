#include <iostream>
#include "IOSubSystem.hpp"
#include "MainWindow.hpp"
#include <gtkmm.h>


IOSubSystem::IOSubSystem()
{
  m_Name = "InputOutput";
  std::cout << "In IOSubsystem contructor" << std::endl; 
}

void IOSubSystem::Create()
{
  std::cout << "\nin IOSubsystem::Create\n" << std::endl;

  //These widgets can come from a ui file or direct from code
  //
  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(15);
  m_Grid.set_column_spacing(20);
    
  // call MainWindow constructor
  MainWindow mainWindow(m_Grid);
}
