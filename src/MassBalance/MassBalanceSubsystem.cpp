#include <iostream>
#include "MassBalanceSubsystem.hpp"


MassBalanceSubsystem::MassBalanceSubsystem() {
    m_Name = "Mass Balance";
    std::cout << "In MassBalanceSubsystem contructor" << std::endl; 
}

void MassBalanceSubsystem::Create() {
  std::cout << "in MassBalanceSubsystem::Create" << std::endl;


  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      auto s = Glib::ustring::compose("button (%1,%2)", i, j);
      auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
      m_Grid.attach(*pButton, i, j);
    }
  }
}
