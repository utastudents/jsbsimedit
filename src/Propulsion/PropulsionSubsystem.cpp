#include <iostream>
#include "PropulsionSubsystem.hpp"


PropulsionSubsystem::PropulsionSubsystem() {
    m_Name = "Propulsion";
    std::cout << "In PropulsionSubsystem contructor" << std::endl; 
}

void PropulsionSubsystem::Create() {
  std::cout << "in PropulsionSubsystem::Create" << std::endl;


  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

// i is length # j is height #
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      auto s = Glib::ustring::compose("button (%1,%2)", i, j);
      auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
      m_Grid.attach(*pButton, i, j);
    }
  }
}
