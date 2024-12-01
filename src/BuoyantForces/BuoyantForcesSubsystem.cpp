#include <iostream>
#include "inc/XML_api.hpp"
#include "BuoyantForcesSubsystem.hpp"
#include "Component.hpp"


int BuoyantForcesSubsystem::m_rows = 0;
int BuoyantForcesSubsystem::m_tab_count = 0;

BuoyantForcesSubsystem::BuoyantForcesSubsystem()
{

  m_Name = "Buoyant Forces";
  std::cout << "In BuoyantForcesSubsystem contructor" << std::endl;
}

void BuoyantForcesSubsystem::Create()
{
  std::cout << "in BuoyantForcesSubsystem::Create" << std::endl;
  // auto node=xmlptr()->GetNode("buoyant_forces");

  // These widgets can come from a ui file or direct from code

  /* set the spacing to 10 on x and 10 on y */

  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  m_notebook.set_margin_bottom(10);
  m_notebook.set_margin_start(10);
  m_notebook.set_margin_end(10);
  m_notebook.set_expand();
  m_notebook.set_sensitive(false);

  m_checkbutton.set_label("Enable/Disable");
  m_checkbutton.set_margin_top(10);
  m_checkbutton.set_margin_start(10);

  m_checkbutton.signal_toggled().connect(
    sigc::mem_fun(*this, &BuoyantForcesSubsystem::on_button_toggled));

  m_Grid.attach(m_checkbutton, 0, m_rows++);
  m_Grid.attach(m_notebook, 0, m_rows++);

  LoadStringLists();

  // Create "Gas Cell" Tab
  std::string gc_name = m_gascell.getName();
  m_pages[gc_name] = std::make_unique<Gtk::Grid>();
  SetupTab(*m_pages[gc_name]);
  m_notebook.append_page(*m_pages[gc_name], gc_name);


  // Track switching tabs
  m_notebook.signal_switch_page().connect(sigc::mem_fun(*this,
      &BuoyantForcesSubsystem::on_notebook_switch_page));


  // Load XML data for testing
  try {
    LoadXMLData();
    std::cout << "XML data loaded successfully." << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error loading XML in Create(): " << e.what() << std::endl;
  }
}

void BuoyantForcesSubsystem::SaveXMLData() {
    // code
}

void BuoyantForcesSubsystem::LoadXMLData() {
    try {
        // auto buoyantForcesNode = xmlptr()->GetNode("/fdm_config/buoyant_forces");

        // temp file for testing
        doc.LoadFileAndParse({"../../../data/aircraft/Submarine_Scout/Submarine_Scout.xml"});
        auto buoyantForcesNode = doc.GetNode("/fdm_config/buoyant_forces");
        auto gasCellNode = buoyantForcesNode.FindChild("gas_cell");

        // todo: make sure this works
        std::vector<JSBEdit::XMLNode> ballonetNodes;

        if (buoyantForcesNode) {
            std::cout << "buoyant_forces node found!" << std::endl;
            m_checkbutton.set_active(true);     // Enables the button

        } else {
            std::cout << "buoyant_forces node NOT found!" << std::endl;
            m_checkbutton.set_active(false);    // Disables the button
        }

        if (gasCellNode) {
            SetWidgetsFromNodes(gasCellNode, 0);

            for (int i=5; i < gasCellNode.GetChildren().size(); i++) {
                if (gasCellNode.GetChild(i).GetName() == "ballonet") {
                    ballonetNodes.push_back(gasCellNode.GetChild(i));
                }   
            }
            std::cout << "Airship has " << ballonetNodes.size() << " ballonet(s)" << std::endl;
            SetDropDownFromNode(ballonetNodes.back(), "ballonet", std::to_string(ballonetNodes.size()), 
                                m_ballonetStringList, "# of Ballonets", 0);
        }

        if (ballonetNodes.size() > 0) {
            for (int i=0; i < ballonetNodes.size(); i++) {
                SetWidgetsFromNodes(ballonetNodes.at(i), i+1);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading XML data: " << e.what() << std::endl;
        m_checkbutton.set_active(false);    // Default to disabled in case of error
    }
}

void BuoyantForcesSubsystem::SetWidgetsFromNodes(JSBEdit::XMLNode& root, int tabIndex) {
    std::cout << root.GetName() << std::endl;
    std::cout << "   Gas Type: " << root.GetAttribute("type").second << std::endl;

    std::string rootName = ((tabIndex == 0) ? "gas_cell" : "ballonet");
    SetDropDownFromNode(root, rootName, "type", m_gasStringList, "Gas Type", tabIndex);
    
    auto locationNode = root.FindChild("location");
    if (locationNode) {
        std::cout << "      Location (unit: " << locationNode.GetAttribute("unit").second << "): "
                  << "X=" << locationNode.FindChild("x").GetText() << ", "
                  << "Y=" << locationNode.FindChild("y").GetText() << ", "
                  << "Z=" << locationNode.FindChild("z").GetText() << std::endl;

        SetDropDownFromNode(locationNode, "location", "unit", m_measurementStringList, "Location", tabIndex);
    }

    // Dimensions
    auto x_dimensionNode = root.FindChild("x_radius");
    if (x_dimensionNode) {
        std::cout << "      X Dimension = " << x_dimensionNode.GetText() << " (unit = " 
                  << x_dimensionNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(x_dimensionNode, "x_radius", "unit", m_measurementStringList, "Dimensions", tabIndex);
    }

    auto y_dimensionNode = root.FindChild("y_radius");
    if (y_dimensionNode) {
        std::cout << "      Y Dimension = " << y_dimensionNode.GetText() << " (unit = " 
                  << y_dimensionNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(y_dimensionNode, "y_radius", "unit", m_measurementStringList, "Dimensions", tabIndex);
    }

    auto z_dimensionNode = root.FindChild("z_radius");
    if (z_dimensionNode) {
        std::cout << "      Z Dimension = " << z_dimensionNode.GetText() << " (unit = " 
                  << z_dimensionNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(z_dimensionNode, "z_radius", "unit", m_measurementStringList, "Dimensions", tabIndex);
    }

    // Other Data
    auto overpressureNode = root.FindChild("max_overpressure");
    if (overpressureNode) {
        std::cout << "      Max Overpressure = " << overpressureNode.GetText() << " (unit = " 
                  << overpressureNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(overpressureNode, "max_overpressure", "unit", m_pressureStringList, "Max Overpressure", tabIndex);
    }

    auto valveCoefficientNode = root.FindChild("valve_coefficient");
    if (valveCoefficientNode) {
        std::cout << "      Valve Coefficient = " << valveCoefficientNode.GetText() << " (unit = "
                  << valveCoefficientNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(valveCoefficientNode, "valve_coefficient", "unit", m_valveStringList, "Valve Coefficient", tabIndex);
    }

    auto fullnessNode = root.FindChild("fullness");
    if (fullnessNode) {
        std::cout << "      Fullness = " << fullnessNode.GetText() << std::endl;
    }
}

void BuoyantForcesSubsystem::SetDropDownFromNode(JSBEdit::XMLNode& node, const std::string& nodeName, 
                                                 const std::string& attributeName, const Glib::RefPtr<Gtk::StringList>& stringList, 
                                                 const std::string& dropdownLabel, int tabIndex) {
    if (node.GetName() == nodeName) {
        Glib::ustring dataRead;
        if (nodeName == "ballonet" && tabIndex == 0)     dataRead = attributeName;
        else                            dataRead = node.GetAttribute(attributeName).second;
        int foundIndex = -1;

        for (int i = 0; i < stringList->get_n_items(); i++) {
            if (stringList->get_string(i) == dataRead) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            std::string keyString = dropdownLabel + " " + std::to_string(tabIndex);

            if (m_dropdowns.find(keyString) != m_dropdowns.end())
                m_dropdowns[keyString]->set_selected(foundIndex);
            else
                std::cerr << "Dropdown with key " << keyString << " not found!" << std::endl;
        } else {
            std::cerr << "Unit " << dataRead << " not found in list for " << nodeName << std::endl;
        }
    }
}

Component::Unit BuoyantForcesSubsystem::GetUnitFromString(const std::string& unit_string) const {
    Component::Unit UnitType;

    if (unit_string == "width")     { UnitType = Component::Unit::WIDTH; }
    if (unit_string == "radius")    { UnitType = Component::Unit::RADIUS; }
    
    if (unit_string == "PA")    { UnitType = Component::Unit::PA; }
    if (unit_string == "PSI")   { UnitType = Component::Unit::PSI; }
    
    if (unit_string == "M")     { UnitType = Component::Unit::M; }
    if (unit_string == "IN")    { UnitType = Component::Unit::IN; }
    
    if (unit_string == "FT4*SEC/SLUG")  { UnitType = Component::Unit::FT4_SEC_SLUG; }
    if (unit_string == "M4*SEC/KG")     { UnitType = Component::Unit::M4_SEC_KG; }
    
    if (unit_string == "lbs ft / sec")      { UnitType = Component::Unit::LBS_FT_SEC; }
    if (unit_string == "lb ft / (sec R)")   { UnitType = Component::Unit::LB_FT_SEC_R; }
    
    if (unit_string == "ft^3 / sec")     { UnitType = Component::Unit::FT3_SEC; }

    return UnitType;
}

void BuoyantForcesSubsystem::on_button_toggled() {
  bool enable = m_checkbutton.get_active();

  if (enable) 
    std::cout << "Buoyant Forces is ENABLED" << std::endl;
  else 
    std::cout << "Buoyant Forces is DISABLED" << std::endl;

  m_notebook.set_sensitive(enable);
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

        if (tab_index == 0)
            m_gascell.setGasType(selected_gas_type);
        else 
            m_ballonets[tab_index-1].setGasType(selected_gas_type);
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
            if (tab_index == 0) 
                m_gascell.setLocationUnit(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setLocationUnit(selected_unit_type);
        }
        else if (key.find("Dimensions") != std::string::npos) {
            selected_string = m_measurementStringList->get_string(selected);
            if (tab_index == 0) 
                m_gascell.setDimensionsUnit(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setDimensionsUnit(selected_unit_type);
        }
        else if (key.find("Dim") != std::string::npos) {
            selected_string = m_shapeStringList->get_string(selected);
            if (tab_index == 0) 
                m_gascell.setDimensionsShape(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setDimensionsShape(selected_unit_type);
        }
        else if (key.find("Max Overpressure") != std::string::npos) {
            selected_string = m_pressureStringList->get_string(selected);
            if (tab_index == 0) 
                m_gascell.setPressureUnit(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setPressureUnit(selected_unit_type);
        }
        else if (key.find("Valve Coefficient") != std::string::npos) {
            selected_string = m_valveStringList->get_string(selected);
            if (tab_index == 0) 
                m_gascell.setValveCoefficientUnit(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setValveCoefficientUnit(selected_unit_type);
        }
        else if (key.find("Blower Value") != std::string::npos) {
            selected_string = m_blowerStringList->get_string(selected);
            m_ballonets[tab_index-1].setBlowerUnit(selected_unit_type);
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

