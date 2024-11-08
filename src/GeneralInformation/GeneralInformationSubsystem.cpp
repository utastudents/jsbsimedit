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

  //create labels, textboxes, etc.
  auto aircraftNameLabel = Gtk::make_managed<Gtk::Label>("Aircraft Name");
  auto aircraftNameTextbox = Gtk::make_managed<Gtk::Entry>();
  aircraftNameTextbox->set_text("Place holder."); //load aircraft name here

  auto filePathLabel = Gtk::make_managed<Gtk::Label>("File Path");
  auto filePathTextbox = Gtk::make_managed<Gtk::Entry>();
  filePathTextbox->set_text("Place holder."); //load file path here


  auto releaseLevelLabel = Gtk::make_managed<Gtk::Label>("Release Level");
  auto releaseLevelDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
  //load release levels
  releaseLevelDropDown->append("ALPHA");
  releaseLevelDropDown->append("BETA");

  releaseLevelDropDown->set_active(0); //sets ALPHA default


  m_Grid.attach(*aircraftNameLabel, 0, 0);
  m_Grid.attach(*aircraftNameTextbox, 1, 0);

  m_Grid.attach(*filePathLabel, 3, 0);
  m_Grid.attach(*filePathTextbox, 4, 0);

  m_Grid.attach(*releaseLevelLabel, 0, 2);
  m_Grid.attach(*releaseLevelDropDown, 1, 2);

}
