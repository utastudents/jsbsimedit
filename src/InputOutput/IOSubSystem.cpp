#include <iostream>
#include "IOSubSystem.hpp"
#include "MainWindow.hpp"

IOSubSystem::IOSubSystem()
{
    m_Name = "InputOutput";
    std::cout << "In IOSubsystem contructor" << std::endl; 
}

void IOSubSystem::Create()
{
  std::cout << "in IOSubsystem::Create" << std::endl;

  //These widgets can come from a ui file or direct from code
  //
  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);
    
  // call constructor
  MainWindow mainWindow;
    
  // creates name label and text box, then attaches them to the grid
  /*
  auto nameLabel = Gtk::make_managed<Gtk::Label>("Name(*)");
  auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
  m_Grid.attach(*nameLabel, 0, 0);
  m_Grid.attach(*nameTextbox, 1, 0);
  */

  /*
  this simply creates a grid of toggle buttons
   * to demonstrate the scrolled window.
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      auto s = Glib::ustring::compose("button (%1,%2)", i, j);
      auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
      m_Grid.attach(*pButton, i, j);
    }
  }
*/
}
