#include <iostream>

#include "BuoyantForcesSubsystem.hpp"
#include "Component.hpp"


BuoyantForcesSubsystem::BuoyantForcesSubsystem(std::string N)
                :m_name(N)
{
    std::cout << "In BuoyantForcesSubsystem contructor" << std::endl;
}

void BuoyantForcesSubsystem::Create()
{
  std::cout << "in BuoyantForcesSubsystem::Create" << std::endl;

  //These widgets can come from a ui file or direct from code
  //
  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  m_notebook.set_margin(10);
  m_notebook.set_expand();

  m_Grid.attach(m_notebook, 0, 0);

  m_pages.push_back(std::make_unique<Gtk::Grid>());
  SetupTab(*m_pages.back());
  m_notebook.append_page(*m_pages.back(), "Gas Cell");
}

void BuoyantForcesSubsystem::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to tab with index " << page_num << std::endl;
}

// void BuoyantForcesSubsystem::setupGasCellTab()
// {	
//   //creating the widgets for the cell tabl
// 	Gtk::Box gasCellBox(Gtk::ORIENTATION_VERTICAL, 10);
	
//   // create lavel for gas cell tab
//   Gtk::Label gasCellNameLabel("Gas Cell: ");
// 	gasCellNameLabel.set_halign(Gtk::ALIGN_START);
// 	gasCellBox.pack_start(gasCellNameLabel);
	
//   //next creating the drop down menu
// 	Gtk::Label gasTypeLabel("Select Gas Type:");
// 	gasTypeLabel.set_halign(Gtk::ALIGN_START);
// 	gasCellBox.pack_start(gasTypeLabel);

//   //adding elements to drop down menu
// 	m_gasTypeMenu.append("Air");
// 	m_gasTypeMenu.append("Helium");
// 	m_gasTypeMenu.append("Hydrogen");

// 	m_gasTypeMenu.set_active(0); // Set default to Air
// 	gasCellBox.pack_start(m_gasTypeMenu);

// }

void BuoyantForcesSubsystem::BuildTabs() 
{
  std::cout << "in BuoyantForcesSubsystem::BuildTabs" << std::endl;

  for (int i = 0; i < Component::getBallonetCount(); i++) 
  {
    Gtk::Grid grid;
    grid.set_row_spacing(10);
    grid.set_column_spacing(10);
    m_notebook.append_page(grid, "Ballonet " + std::to_string(i+1));
  }
}

void BuoyantForcesSubsystem::SetupTab(Gtk::Grid& p_grid) 
{
  // Drop Down Menu for Gas Type
  auto dropdown_gas = Gtk::make_managed<Gtk::DropDown>();
  auto gasItems = Gtk::StringList::create({"Air", "Helium", "Hydrogen"});
  auto label_gas = Gtk::make_managed<Gtk::Label>("Gas Type");

  dropdown_gas->set_model(gasItems);
  dropdown_gas->set_selected(0);
  dropdown_gas->set_expand(false);
  dropdown_gas->set_show_arrow(true);
  dropdown_gas->set_size_request(150, -1);
  label_gas->set_size_request(250, -1);

  p_grid.attach(*label_gas, 0,0);
  p_grid.attach(*dropdown_gas, 1, 0);


  // Drop Down Menu for Units (for Location)
  AddUnitsDropDown(p_grid, "Location", 0, 1);

  // Entry Texts for Location
  AddEntry(p_grid, "x", 0, 3, false);
  AddEntry(p_grid, "y", 0, 4, false);
  AddEntry(p_grid, "z", 0, 5, false);


    // Drop Down Menu for Units (for Dimensions)
  AddUnitsDropDown(p_grid, "Dimensions", 0, 6);

  // Entry Texts for Dimensions
  AddEntry(p_grid, "x", 0, 7, false);
  AddEntry(p_grid, "y", 0, 8, false);
  AddEntry(p_grid, "z", 0, 9, false);

  // Entry Text for Max Overpressure
  AddEntry(p_grid, "Max Overpressure", 0, 10, true);

  // Entry Text for Valve Coefficient
  AddEntry(p_grid, "Valve Coefficient", 0, 11, true);

  // Entry Text for Fullness
  AddEntry(p_grid, "Fullness", 0, 12, false);

  // Entry Text for # of Ballonets
  AddEntry(p_grid, "Ballonets", 0, 13, false);
}

void BuoyantForcesSubsystem::AddUnitsDropDown(Gtk::Grid& p_grid, std::string label, int col, int row) {
  auto dropdown_units = Gtk::make_managed<Gtk::DropDown>();
  auto unitItems = Gtk::StringList::create({});
  auto dropdown_label = Gtk::make_managed<Gtk::Label>(label);

  for (int i = static_cast<int>(Component::Unit::WIDTH); i <= static_cast<int>(Component::Unit::FT3_SEC); ++i)
  {
    Component::Unit unit = static_cast<Component::Unit>(i);
    unitItems->append(Component::unitToString(unit));
  }

  dropdown_units->set_model(unitItems);
  dropdown_units->set_selected(3);
  dropdown_units->set_expand(false);
  dropdown_units->set_show_arrow(true); 

  p_grid.attach(*dropdown_label, col, row);
  p_grid.attach(*dropdown_units, ++col, row);
}

void BuoyantForcesSubsystem::AddEntry(Gtk::Grid& p_grid, std::string label, int col, int row, bool hasDDMenu)
{
  auto entry_number = Gtk::make_managed<Gtk::Entry>();
  auto entry_label = Gtk::make_managed<Gtk::Label>(label);

  entry_number->set_max_length(50);
  entry_number->select_region(0, entry_number->get_text_length());
  entry_number->set_expand(false);
  entry_number->set_input_purpose(Gtk::InputPurpose::NUMBER);

  p_grid.attach(*entry_label, col, row);
  p_grid.attach(*entry_number, ++col, row);
  if (hasDDMenu) AddUnitsDropDown(p_grid, "", ++col, row);
}
