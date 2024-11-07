#include <iostream>

#include "GeneralInformationSubsystem.hpp"

GeneralInformationSubsystem::GeneralInformationSubsystem()
{
    m_Name = "GeneralInformation";
    std::cout << "In GeneralInformationSubsystem constructor" << std::endl; 
}

void GeneralInformationSubsystem::Create()
{
  std::cout << "in GeneralInformationSubsystem::Create" << std::endl;

  //These widgets can come from a ui file or direct from code
  //
  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  /* this simply creates a grid of toggle buttons
   * to demonstrate the scrolled window. */
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
