#include <iostream>
#include "inc/XML_api.hpp"
#include "BuoyantForcesSubsystem.hpp"
#include "Component.hpp"


int BuoyantForcesSubsystem::m_rows = 0;
int BuoyantForcesSubsystem::m_tab_count = 0;

BuoyantForcesSubsystem::BuoyantForcesSubsystem()
{

  m_Name = "BuoyantForces";
  std::cout << "In BuoyantForcesSubsystem contructor" << std::endl;
}

void BuoyantForcesSubsystem::Create()
{
  std::cout << "in BuoyantForcesSubsystem::Create" << std::endl;
  //auto node=xmlptr()->GetNode("buoyant_forces");

  // These widgets can come from a ui file or direct from code

  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  m_notebook.set_margin(10);
  m_notebook.set_expand();

  m_Grid.attach(m_notebook, 0, m_rows++);

    try
  {   
                                               // file  paths will need some work to correlate to our buoyant forces
    //temp file for testing
    doc.LoadFileAndParse({"../../../data/aircraft/weather-balloon/weather-balloon.xml"});
    
    // temporarilly using doc instead of xmlptr() so we can test if it is pulling from file
    auto node = doc.GetNode("fdm_config"); // root node
    auto node_BuoyantForces = doc.GetNode("/fdm_config/buoyant_forces");
    auto node_GasCell = doc.GetNode("/fdm_config/buoyant_forces/gas_cell");
  
  //todo: make sure this works
    std::vector <JSBEdit::XMLNode> node_ballonett = node_BuoyantForces.GetChildren();

    if (node_BuoyantForces)
    {
      std::cout << "Buoyant Forces node found: " << std::endl;
    }
    if (node_GasCell)
    {
      std::cout << "Gas Cell: " << node_GasCell.GetAttribute("type").second << std::endl;
    }
  }
  catch(const std::exception& e){
    std::cout << "got caught" << std::endl;
  }

  LoadStringLists();
  
  // Create "Gas Cell" Tab
  std::string gc_name = m_gascell.getName();
  m_pages[gc_name] = std::make_unique<Gtk::Grid>();
  SetupTab(*m_pages[gc_name]);
  m_notebook.append_page(*m_pages[gc_name], gc_name);


  // Track switching tabs
  m_notebook.signal_switch_page().connect(sigc::mem_fun(*this,
      &BuoyantForcesSubsystem::on_notebook_switch_page));
}

Component::Unit BuoyantForcesSubsystem::GetUnitFromString(const std::string& unit_string) const {
    Component::Unit UnitType;

    if (unit_string == "WIDTH")     { UnitType = Component::Unit::WIDTH; }
    if (unit_string == "RADIUS")    { UnitType = Component::Unit::RADIUS; }
    
    if (unit_string == "PA")    { UnitType = Component::Unit::PA; }
    if (unit_string == "PSI")   { UnitType = Component::Unit::PSI; }
    
    if (unit_string == "M")     { UnitType = Component::Unit::M; }
    if (unit_string == "IN")    { UnitType = Component::Unit::IN; }
    
    if (unit_string == "FT4 * SEC / SLUG")  { UnitType = Component::Unit::FT4_SEC_SLUG; }
    if (unit_string == "M4 * SEC / KG")     { UnitType = Component::Unit::M4_SEC_KG; }
    
    if (unit_string == "LBS FT / SEC")      { UnitType = Component::Unit::LBS_FT_SEC; }
    if (unit_string == "LB FT / (SEC R)")   { UnitType = Component::Unit::LB_FT_SEC_R; }
    
    if (unit_string == "FT3 / SEC")     { UnitType = Component::Unit::FT3_SEC; }

    return UnitType;
}

void BuoyantForcesSubsystem::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  Gtk::Widget* tab = m_notebook.get_nth_page(page_num);
  std::string tab_name = m_notebook.get_tab_label_text(*tab);
  std::cout << "Switched to '" << tab_name << "' tab with index " << page_num << std::endl;
}

void BuoyantForcesSubsystem::on_dropdown_changed(const std::string& key) {
    auto& dropdown = m_dropdowns[key];
    const auto selected = dropdown->get_selected();
    int tab_index = stoi(std::string(1, key.back()));
    std::string selected_string;

    if (key.find("Gas Type") != std::string::npos) {
        selected_string = m_gasStringList->get_string(selected);
        Component::GasType selected_gas_type = static_cast<Component::GasType>(selected);

        if (tab_index == 0) {
            m_gascell.setGasType(selected_gas_type);

            std::cout << "Selected Gas Type (for Gas Cell): " << selected_string
                      << std::endl;
        } else {
            m_ballonets[tab_index-1].setGasType(selected_gas_type);

            std::cout << "Selected Gas Type (for Ballonet " << tab_index << "): " << selected_string
                      << std::endl;
        }
    } 

    else if (key.find("# of Ballonets") != std::string::npos) {
        selected_string = m_ballonetStringList->get_string(selected);

        m_gascell.setBallonetCount(selected);
        BuildTabs();
    } 
    
    else {
        Component::Unit selected_unit_type = GetUnitFromString(selected_string);

        if (key.find("Loc") != std::string::npos) {
            selected_string = m_measurementStringList->get_string(selected);
            if (tab_index == 0) {
                m_gascell.setLocationUnit(selected_unit_type);
                std::cout << "Set Gas Cell's Location Units to '" << selected_string << "'" << std::endl;
            } 
            else {
                m_ballonets[tab_index-1].setLocationUnit(selected_unit_type);
                std::cout << "Set Ballonet's Location Units to '" << selected_string << "'" << std::endl;
            }
        }
        else if (key.find("Dimensions") != std::string::npos) {
            selected_string = m_measurementStringList->get_string(selected);
            if (tab_index == 0) {
                m_gascell.setDimensionsUnit(selected_unit_type);

                std::cout << "Set Gas Cell's Dimensions Units to '" << selected_string << "'" << std::endl;
            }
            else {
                m_ballonets[tab_index-1].setDimensionsUnit(selected_unit_type);

                std::cout << "Set Ballonet's Dimensions Units to '" << selected_string << "'" << std::endl;
            }
        }
        else if (key.find("Dim") != std::string::npos) {
            selected_string = m_shapeStringList->get_string(selected);
            if (tab_index == 0) {
                m_gascell.setDimensionsShape(selected_unit_type);

                std::cout << "Set Gas Cell's Dimensions Shape to '" << selected_string << "'" << std::endl;
            }
            else {
                m_ballonets[tab_index-1].setDimensionsShape(selected_unit_type);

                std::cout << "Set Ballonet's Dimensions Shape to '" << selected_string << "'" << std::endl;
            }
        }
        else if (key.find("Max Overpressure") != std::string::npos) {
            selected_string = m_pressureStringList->get_string(selected);
            if (tab_index == 0) {
                m_gascell.setPressureUnit(selected_unit_type);

                std::cout << "Set Gas Cell's Max Overpressure Units to '" << selected_string << "'" << std::endl;
            }
            else {
                m_ballonets[tab_index-1].setPressureUnit(selected_unit_type);

                std::cout << "Set Ballonet's Max Overpressure Units to '" << selected_string << "'" << std::endl;
            }
        }
        else if (key.find("Valve Coefficient") != std::string::npos) {
            selected_string = m_valveStringList->get_string(selected);
            if (tab_index == 0) {
                m_gascell.setValveCoefficientUnit(selected_unit_type);

                std::cout << "Set Gas Cell's Valve Coefficient Units to '" << selected_string << "'" << std::endl;
            }
            else {
                m_ballonets[tab_index-1].setValveCoefficientUnit(selected_unit_type);

                std::cout << "Set Ballonet's Valve Coefficient Units to '" << selected_string << "'" << std::endl;
            }
        }
        else if (key.find("Blower Value") != std::string::npos) {
            selected_string = m_blowerStringList->get_string(selected);
            m_ballonets[tab_index-1].setBlowerUnit(selected_unit_type);

            std::cout << "Set Ballonet's Blower Value Units to '" << selected_string << "'" << std::endl;
        }

    }

    std::cout << "Dropdown '" << key << "' changed, Row = " << selected
              << ", String = " << selected_string << std::endl;
}

void BuoyantForcesSubsystem::on_entry_activate(const std::string& key) {
    auto it = m_entries.find(key);
    if (it != m_entries.end()) {
        Glib::ustring input = it->second->get_text();  // Retrieve text from the entry box
        std::cout << "'" << key << "' activated with input: " << input << std::endl;
    } 
}

// void BuoyantForcesSubsystem:: on_ballonetcount_changed()
// {
//   int selected_value = m_dropdowns["Ballonet"]->get_selected();
//   if(selected_value >= 0)
//   {
//   int ballonetCount= selected_value;
//   Component :: setBallonetCount(ballonetCount);
//   std::cout << "Selected Ballonet Count:" <<ballonetCount <<std::endl;

//   BuildTabs();
//   }
// }

void BuoyantForcesSubsystem::LoadStringLists() {
  m_gasStringList = Gtk::StringList::create({"AIR", "HELIUM", "HYDROGEN"});

  m_shapeStringList = Gtk::StringList::create({});
  for (int i = static_cast<int>(Component::Unit::WIDTH); i <= static_cast<int>(Component::Unit::RADIUS); ++i) {
    Component::Unit unit = static_cast<Component::Unit>(i);
    m_shapeStringList->append(Component::unitToString(unit));
  }

  m_measurementStringList = Gtk::StringList::create({});
  for (int i = static_cast<int>(Component::Unit::M); i <= static_cast<int>(Component::Unit::IN); ++i) {
    Component::Unit unit = static_cast<Component::Unit>(i);
    m_measurementStringList->append(Component::unitToString(unit));
  }

  m_pressureStringList = Gtk::StringList::create({});
  for (int i = static_cast<int>(Component::Unit::PA); i <= static_cast<int>(Component::Unit::PSI); ++i) {
    Component::Unit unit = static_cast<Component::Unit>(i);
    m_pressureStringList->append(Component::unitToString(unit));
  }
  
  m_valveStringList = Gtk::StringList::create({});
  for (int i = static_cast<int>(Component::Unit::FT4_SEC_SLUG); i <= static_cast<int>(Component::Unit::M4_SEC_KG); ++i) {
    Component::Unit unit = static_cast<Component::Unit>(i);
    m_valveStringList->append(Component::unitToString(unit));
  }
  
  m_blowerStringList = Gtk::StringList::create({});
  for (int i = static_cast<int>(Component::Unit::FT3_SEC); i <= static_cast<int>(Component::Unit::FT3_SEC); ++i) {
    Component::Unit unit = static_cast<Component::Unit>(i);
    m_blowerStringList->append(Component::unitToString(unit));
  }

  m_ballonetStringList = Gtk::StringList::create({"0", "1", "2", "3", "4", "5"});
}

void BuoyantForcesSubsystem::AddDropDown(Gtk::Grid& p_grid, std::string label, int col, Glib::RefPtr<Gtk::StringList> stringlist) {
  // DropDown Key will be appended with current tab count
  std::string key_text = label + " " + std::to_string(m_tab_count);
  auto dropdown_label = Gtk::make_managed<Gtk::Label>(label);

  m_dropdowns[key_text] = std::make_unique<Gtk::DropDown>();
  m_dropdowns[key_text]->set_model(stringlist);
  m_dropdowns[key_text]->set_expand(false);
  m_dropdowns[key_text]->set_show_arrow(true);
  m_dropdowns[key_text]->set_size_request(150, -1);
  m_dropdowns[key_text]->set_margin_top(5);
  m_dropdowns[key_text]->set_margin_bottom(5);

  if (m_entries.find(key_text) == m_entries.end()) {
    p_grid.attach(*dropdown_label, 0, m_rows);
  }

  p_grid.attach(*m_dropdowns[key_text], col, m_rows++);

  m_dropdowns[key_text]->property_selected().signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_dropdown_changed), key_text));
}

void BuoyantForcesSubsystem::BuildTabs() 
{
    int current = m_ballonets.size();
    int target = m_gascell.getBallonetCount();

    // Add Ballonet Objects 
    while (current < target) {
        std::cout << "Building Ballonet " << current << " Object" << std::endl;
        m_ballonets.emplace_back("Ballonet " + std::to_string(current + 1));
        current++;
    }

    // Remove Ballonet Objects
    while (current > target) {
        std::cout << "Destroying Ballonet " << current << " Object" << std::endl;
        m_ballonets.pop_back();
        current--;
    }

    // Add Ballonet Tab
    while (m_tab_count < target) {
        Gtk::Grid grid;
        grid.set_row_spacing(10);
        grid.set_column_spacing(10);

        std::string b_name = m_ballonets[m_tab_count++].getName();
        m_pages[b_name] = std::make_unique<Gtk::Grid>();
        SetupTab(*m_pages[b_name]);

        m_notebook.append_page(*m_pages[b_name], b_name);
    }

    // Remove Ballonet Tab
    while (m_tab_count > target) {
        m_notebook.remove_page(m_tab_count--);
    }
}

void BuoyantForcesSubsystem::SetupTab(Gtk::Grid& p_grid) 
{
  AddDropDown(p_grid, "Gas Type", 1, m_gasStringList);

  AddDropDown(p_grid, "Location", 1, m_measurementStringList);
  AddEntry(p_grid, "x Loc", false);
  AddEntry(p_grid, "y Loc", false);
  AddEntry(p_grid, "z Loc", false);

  AddDropDown(p_grid, "Dimensions", 1, m_measurementStringList);
  AddEntry(p_grid, "x Dim", true);
  AddEntry(p_grid, "y Dim", true);
  AddEntry(p_grid, "z Dim", true);

  AddEntry(p_grid, "Max Overpressure", true);

  AddEntry(p_grid, "Valve Coefficient", true);

  AddEntry(p_grid, "Fullness", false);

  if (m_pages.size() == 1) {
    // Select # of Ballonets
    AddDropDown(p_grid, "# of Ballonets", 1, m_ballonetStringList);
    BuildTabs();

  } else {
    // Input Blower Input
    AddEntry(p_grid, "Blower Input", false);
  }


  /* 


      Add Heat Wisgets Here
  

  */
  
}


void BuoyantForcesSubsystem::AddEntry(Gtk::Grid& p_grid, std::string label, bool hasDDMenu)
{
  std::string key_text = label + " " + std::to_string(m_tab_count);
  auto entry_label = Gtk::make_managed<Gtk::Label>();

  if (label[0] == 'x' || label[0] == 'y' || label[0] == 'z') {
    Glib::ustring label_ch = label.substr(0,1);
    entry_label->set_text(label_ch);
  } else {
    entry_label->set_text(label);
  }

  m_entries[key_text] = std::make_unique<Gtk::Entry>();
  m_entries[key_text]->set_max_length(50);
  m_entries[key_text]->select_region(0, m_entries[key_text]->get_text_length());
  m_entries[key_text]->set_expand(false);
  m_entries[key_text]->set_input_purpose(Gtk::InputPurpose::NUMBER);
  m_entries[key_text]->set_margin_top(5);
  m_entries[key_text]->set_margin_bottom(5);

  m_entries[key_text]->signal_activate().connect(
    sigc::bind(sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_entry_activate), key_text));
  
  p_grid.attach(*entry_label, 0, m_rows);

  if (hasDDMenu) {
    p_grid.attach(*m_entries[key_text], 1, m_rows);

    auto empty_cell = Gtk::make_managed<Gtk::Label>();
    empty_cell->set_size_request(5,5);
    p_grid.attach(*empty_cell, 2, m_rows);

    if (label.find("Dim") != std::string::npos)     { AddDropDown(p_grid, label, 3, m_shapeStringList);  }
    if (label == "Max Overpressure")                { AddDropDown(p_grid, label, 3, m_pressureStringList);     }
    if (label == "Valve Coefficient")               { AddDropDown(p_grid, label, 3, m_valveStringList);        }
    if (label == "Blower Input")                    { AddDropDown(p_grid, label, 3, m_blowerStringList);       }
  } else {
      p_grid.attach(*m_entries[key_text], 1, m_rows++);
  }
}

/* DOUBLE CHECK BEFORE DELETING 11/29 -Noorah

    m_dropdowns["Gas Type"] = std::make_unique<Gtk::DropDown>();
    m_dropdowns["Gas Type"]->set_model(m_gasStringList);
    m_dropdowns["Gas Type"]->set_selected(0);
    m_dropdowns["Gas Type"]->set_expand(false);
    m_dropdowns["Gas Type"]->set_show_arrow(true);
    m_dropdowns["Gas Type"]->set_size_request(150, -1);
    label_gas->set_size_request(250, -1);

    p_grid.attach(*label_gas, 0, 0);
    p_grid.attach(*m_dropdowns["Gas Type"], 1, 0);

    m_dropdowns["Gas Type"]->property_selected().signal_changed().connect(
        sigc::bind(sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_dropdown_changed), "Gas Type"));

    // Drop Down Menu for Units (for Location)
    AddUnitsDropDown(p_grid, "Location", 0, 1);

    // Entry Texts for Location
    auto input_location_x = AddEntry(p_grid, "x", 0, 3, false);
    input_location_x->signal_changed().connect([this, input_location_x]()
                                               { double locationX = std::stod(input_location_x->get_text()); });

    auto input_location_y = AddEntry(p_grid, "y", 0, 4, false);
    input_location_y->signal_changed().connect([this, input_location_y]()
                                               { double locationY = std::stod(input_location_y->get_text()); });

    auto input_location_z = AddEntry(p_grid, "z", 0, 5, false);
    input_location_z->signal_changed().connect([this, input_location_z]()
                                               { double locationZ = std::stod(input_location_z->get_text()); });

    // Drop Down Menu for Units (for Dimensions)
    AddUnitsDropDown(p_grid, "Dimensions", 0, 6);

    // Entry Texts for Dimensions
    auto input_dimension_x = AddEntry(p_grid, "x", 0, 7, true);
    input_dimension_x->signal_changed().connect([this, input_dimension_x]()
                                                { double dimensionX = std::stod(input_dimension_x->get_text()); });

    auto input_dimension_y = AddEntry(p_grid, "y", 0, 8, true);
    input_dimension_y->signal_changed().connect([this, input_dimension_y]()
                                                { double dimensionY = std::stod(input_dimension_y->get_text()); });

    auto input_dimension_z = AddEntry(p_grid, "z", 0, 9, true);
    input_dimension_z->signal_changed().connect([this, input_dimension_z]()
                                                { double dimensionZ = std::stod(input_dimension_z->get_text()); });

    // Entry Text for Max Overpressure
    // gui dispaly text input field
    auto input_max_overpressure = AddEntry(p_grid, "Max Overpressure", 0, 10, true);

    // conect input to a class variable
    input_max_overpressure->signal_changed().connect([this, input_max_overpressure]()
                                                     {
                                                       maxOverpressure = std::stod(input_max_overpressure->get_text()); // stores value
                                                     });

    // Entry Text for Valve Coefficient
    // gui display text input field
    auto input_valve_coefficient = AddEntry(p_grid, "Valve Coefficient", 0, 11, true);

    input_valve_coefficient->signal_changed().connect([this, input_valve_coefficient]()
                                                      { valveCoefficient = std::stod(input_valve_coefficient->get_text()); });

    // Entry Text for Fullness
    AddEntry(p_grid, "Fullness", 0, 12, false);

    if (m_pages.size() == 1)
    {
      // Select # of Ballonets
      Glib::RefPtr<Gtk::StringList> m_ballonetStringList;

      const std::vector<Glib::ustring> ballonetOptions = {"0", "1", "2", "3", "4", "5"};
      auto label_ballonet = Gtk::make_managed<Gtk::Label>("Ballonet");

      m_ballonetStringList = Gtk ::StringList::create(ballonetOptions);

      m_dropdowns["Ballonet"] = std::make_unique<Gtk::DropDown>();
      m_dropdowns["Ballonet"]->set_model(m_ballonetStringList);
      m_dropdowns["Ballonet"]->set_selected(0);

      m_dropdowns["Ballonet"]->set_expand(false);
      m_dropdowns["Ballonet"]->set_show_arrow(true);
      m_dropdowns["Ballonet"]->set_size_request(150, -1);

      m_dropdowns["Ballonet"]->property_selected().signal_changed().connect(sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_ballonetcount_changed));
      label_ballonet->set_size_request(250, -1);

      p_grid.attach(*label_ballonet, 0, 13);
      p_grid.attach(*m_dropdowns["Ballonet"], 1, 13);
    }
    else
    {

      // Input Blower Input
      auto input_blower_value = AddEntry(p_grid, "Blower input", 0, 13, false);
      input_blower_value->signal_changed().connect([this, input_blower_value]()
                                                   { blowerInput = std::stod(input_blower_value->get_text()); });
    }
  }
*/

  void BuoyantForcesSubsystem::on_ballonetcount_changed()
  {
    int selected_value = m_dropdowns["Ballonet"]->get_selected();
    if (selected_value >= 0)
    {
      int ballonetCount = selected_value;
      Component ::setBallonetCount(ballonetCount);
      std::cout << "Selected Ballonet Count:" << ballonetCount << std::endl;

      BuildTabs();
    }
  }

