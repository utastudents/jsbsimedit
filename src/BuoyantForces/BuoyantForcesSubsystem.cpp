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


  // Gas Cell Tab
  Gtk::Label main("Gas Cell");
  m_pages.push_back(std::make_unique<Gtk::Grid>());
  SetupTab(*m_pages.back());
  m_notebook.append_page(*m_pages.back(), main);


  // Ballonet Tabs
  Gtk::Label bal1("Ballonet 1");
  m_pages.push_back(std::make_unique<Gtk::Grid>());
  SetupTab(*m_pages.back());
  m_notebook.append_page(*m_pages.back(), bal1);

  Gtk::Label bal2("Ballonet 2");
  m_pages.push_back(std::make_unique<Gtk::Grid>());
  SetupTab(*m_pages.back());
  m_notebook.append_page(*m_pages.back(), bal2);

  Gtk::Label bal3("Ballonet 3");
  m_pages.push_back(std::make_unique<Gtk::Grid>());
  SetupTab(*m_pages.back());
  m_notebook.append_page(*m_pages.back(), bal3);


  m_notebook.signal_switch_page().connect(sigc::mem_fun(*this,
      &BuoyantForcesSubsystem::on_notebook_switch_page));
}

void BuoyantForcesSubsystem::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to BYF tab with index " << page_num << std::endl;
}

void BuoyantForcesSubsystem::on_dropdown_changed(const std::string& dropdown_name)
{
  auto& dropdown = m_dropdowns[dropdown_name];
  const auto selected = dropdown->get_selected();
  std::cout << "Dropdown '" << dropdown_name << "' changed: Row = " << selected 
            << ", String = " << (dropdown_name == "Gas Type" ?
                                  m_gasStringList->get_string(selected) : 
                                  m_unitsStringList->get_string(selected)) 
            << std::endl;
}

void BuoyantForcesSubsystem::SetupTab(Gtk::Grid& p_grid) 
{
  // Drop Down Menu for Gas Type
  m_gasStringList = Gtk::StringList::create({"Air", "Helium", "Hydrogen"});
  auto label_gas = Gtk::make_managed<Gtk::Label>("Gas Type");

  m_dropdowns["Gas Type"] = std::make_unique<Gtk::DropDown>();
  m_dropdowns["Gas Type"]->set_model(m_gasStringList);
  m_dropdowns["Gas Type"]->set_expand(false);
  m_dropdowns["Gas Type"]->set_show_arrow(true);
  m_dropdowns["Gas Type"]->set_size_request(150, -1);
  label_gas->set_size_request(250, -1);

  p_grid.attach(*label_gas, 0,0);
  p_grid.attach(*m_dropdowns["Gas Type"], 1, 0);

  m_dropdowns["Gas Type"]->property_selected().signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_dropdown_changed), "Gas Type"));

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

void BuoyantForcesSubsystem::AddUnitsDropDown(Gtk::Grid& p_grid, std::string label, int col, int row) 
{
  m_unitsStringList = Gtk::StringList::create({});
  auto dropdown_label = Gtk::make_managed<Gtk::Label>(label);

  for (int i = static_cast<int>(Component::Unit::WIDTH); i <= static_cast<int>(Component::Unit::FT3_SEC); ++i)
  {
    Component::Unit unit = static_cast<Component::Unit>(i);
    m_unitsStringList->append(Component::unitToString(unit));
  }

  m_dropdowns[label] = std::make_unique<Gtk::DropDown>();
  m_dropdowns[label]->set_model(m_unitsStringList);
  m_dropdowns[label]->set_selected(3);
  m_dropdowns[label]->set_expand(false);
  m_dropdowns[label]->set_show_arrow(true); 

  p_grid.attach(*dropdown_label, col, row);
  p_grid.attach(*m_dropdowns[label], ++col, row);

  m_dropdowns[label]->property_selected().signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_dropdown_changed), label));
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

  if (hasDDMenu) 
  {
      AddUnitsDropDown(p_grid, label, ++col, row);
  }
}
