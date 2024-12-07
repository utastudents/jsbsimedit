#include <iostream>

#include "AeroDynamicsSubsystem.hpp"
#include "AerodynamicsWidget.hpp"

AeroDynamicsSubsystem::AeroDynamicsSubsystem()
{
    m_Name = "Aerodynamics";
    // std::cout << "In AeroDynamicsSubsystem contructor" << std::endl; 
}

void AeroDynamicsSubsystem::Create()
{
  //std::cout << "in AeroDynamicsSubsystem::Create" << std::endl;

  //These widgets can come from a ui file or direct from code
  //
  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  auto aerodynamicsWidget = Gtk::make_managed<AerodynamicsWidget>();
  aerodynamicsWidget->set_expand(true);
  m_Grid.attach(*aerodynamicsWidget,0,0);
}
