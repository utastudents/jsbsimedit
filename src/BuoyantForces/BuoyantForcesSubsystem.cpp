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
  std::cout << "---------------------------------" << std::endl;
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


  // Temporary: Only for Testing
  m_savebutton.set_label("Save");
  m_savebutton.set_margin_top(10);
  m_loadbutton.set_label("Load Submarine_Scout");
  m_loadbutton.set_margin_top(10);

  m_savebutton.signal_clicked().connect(
    std::bind(&BuoyantForcesSubsystem::on_button_clicked, this, "Save"));
  m_loadbutton.signal_clicked().connect(
    std::bind(&BuoyantForcesSubsystem::on_button_clicked, this, "Load"));


  m_Grid.attach(m_checkbutton, 0, m_rows);
  m_Grid.attach(m_loadbutton, 2, m_rows);
  m_Grid.attach(m_savebutton, 3, m_rows++);
  m_Grid.attach(m_notebook, 0, m_rows++);

  LoadStringLists();

  m_buoyantforces.setGasCell(m_gascell);

  // Create "Gas Cell" Tab
  std::string gc_name = m_gascell.getName();
  m_pages[gc_name] = std::make_unique<Gtk::Grid>();
  SetupTab(*m_pages[gc_name]);
  m_notebook.append_page(*m_pages[gc_name], gc_name);


  // Track switching tabs
  m_notebook.signal_switch_page().connect(sigc::mem_fun(*this,
      &BuoyantForcesSubsystem::on_notebook_switch_page));
}

void BuoyantForcesSubsystem::SaveXMLData() {
    UpdateData();

    try {
        // "buoyant_forces" node
        if (m_buoyantforces.isBuoyantForcesActive()) {
            JSBEdit::XMLNode root{m_doc, "<buoyant_forces></buoyant_forces>"};

            JSBEdit::XMLNode gascellNode{m_doc, "<gas_cell></gas_cell>"};
            SetNodesFromWidgets(gascellNode);

            if (m_gascell.getBallonetCount() > 0) {
                std::vector<JSBEdit::XMLNode> ballonetNodes;
                for (int i=0; i < m_ballonets.size(); i++) {
                    ballonetNodes.push_back({m_doc, "<ballonet></ballonet>"});
                }
                SetNodesFromWidgets(ballonetNodes.back());
            }

            root.AddChild(gascellNode);
        }   // else, print nothing if BuoyantForces is disabled

        std::cout << "Saving to 'data/aircraft/Submarine_Scout/Submarine_Scout.xml'" << std::endl;
        // m_doc.Print();
        m_doc.SaveToFile("../../../data/aircraft/Submarine_Scout/Submarine_Scout.xml");

    } catch (const std::exception& e) {
        std::cerr << "Error in SaveXML: " << e.what() << std::endl;
    }
}

void BuoyantForcesSubsystem::LoadXMLData() {
    try {
        // auto buoyantForcesNode = xmlptr()->GetNode("/fdm_config/buoyant_forces");

        // temp file for testing
        std::cout << "Using 'data/aircraft/Submarine_Scout/Submarine_Scout.xml' for Buoyant Forces" << std::endl;
        m_doc.LoadFileAndParse({"../../../data/aircraft/Submarine_Scout/Submarine_Scout.xml"});
        auto buoyantForcesNode = m_doc.GetNode("/fdm_config/buoyant_forces");
        auto gasCellNode = buoyantForcesNode.FindChild("gas_cell");

        // todo: make sure this works
        std::vector<JSBEdit::XMLNode> ballonetNodes;

        if (buoyantForcesNode) {
            std::cout << "   buoyant_forces node found!" << std::endl;
            m_checkbutton.set_active(true);     // Enables the button

        } else {
            std::cout << "   buoyant_forces node NOT found!" << std::endl;
            m_checkbutton.set_active(false);    // Disables the button
        }

        if (gasCellNode) {
            SetWidgetsFromNodes(gasCellNode, 0);

            for (int i=5; i < gasCellNode.GetChildren().size(); i++) {
                if (gasCellNode.GetChild(i).GetName() == "ballonet") {
                    ballonetNodes.push_back(gasCellNode.GetChild(i));
                }   
            }
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

void BuoyantForcesSubsystem::UpdateData() {
    // Fetch all data in widgets and update buoyantforces, gascell, and ballonets
    m_buoyantforces.setHasBuoyantForces(m_checkbutton.get_active());

    for (const auto& [key, dropdownptr] : m_dropdowns) {
        int selectedIndex = dropdownptr->get_selected();

        if (selectedIndex >= 0) {
            Glib::RefPtr<Gtk::StringList> stringlist = std::dynamic_pointer_cast<Gtk::StringList>(dropdownptr->get_model());
            if (stringlist) {
                std::string fixedKey = key.substr(0, key.size()-2);
                if (key.back() == '0') {
                    if (fixedKey == "Gas Type")            m_gascell.setGasType(static_cast<Component::GasType>(selectedIndex));
                    if (fixedKey == "Location")            m_gascell.setLocationUnit(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "Dimensions")          m_gascell.setDimensionsUnit(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "x Dim")               m_gascell.setDimensionsShape(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "Max Overpressure")    m_gascell.setPressureUnit(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "Valve Coefficient")   m_gascell.setValveCoefficientUnit(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "# of Ballonets")      m_gascell.setBallonetCount(std::stoi(stringlist->get_string(selectedIndex)));
                }
                else {
                    int ballonetIndex = key.back() - '0';

                    if (fixedKey == "Gas Type")            m_ballonets[ballonetIndex].setGasType(static_cast<Component::GasType>(selectedIndex));
                    if (fixedKey == "Location")            m_ballonets[ballonetIndex].setLocationUnit(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "Dimensions")          m_ballonets[ballonetIndex].setDimensionsUnit(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "x Dim")               m_ballonets[ballonetIndex].setDimensionsShape(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "Max Overpressure")    m_ballonets[ballonetIndex].setPressureUnit(stringToUnit(stringlist->get_string(selectedIndex)));
                    if (fixedKey == "Valve Coefficient")   m_ballonets[ballonetIndex].setValveCoefficientUnit(stringToUnit(stringlist->get_string(selectedIndex)));
                }
            } else {
                std::cout << "No selection." << std::endl;
            }
        }
    }

    for (const auto& [key, entryptr] : m_entries) {
        std::string currentText = entryptr->get_text();
        double textAsDouble = std::stod(currentText);
        // std::cout << "Current entry text: '" << currentText << "' in " << key << std::endl;

        std::string fixedKey = key.substr(0, key.size()-2);
        if (key.back() == '0') {
            if (fixedKey == "x Loc")                m_gascell.setXLocation(textAsDouble);
            if (fixedKey == "y Loc")                m_gascell.setYLocation(textAsDouble);
            if (fixedKey == "z Loc")                m_gascell.setZLocation(textAsDouble);
            if (fixedKey == "x Dim")                m_gascell.setXDimension(textAsDouble);
            if (fixedKey == "y Dim")                m_gascell.setYDimension(textAsDouble);
            if (fixedKey == "z Dim")                m_gascell.setZDimension(textAsDouble);
            if (fixedKey == "Max Overpressure")     m_gascell.setOverpressure(textAsDouble);
            if (fixedKey == "Valve Coefficient")    m_gascell.setValveCoefficient(textAsDouble);
            if (fixedKey == "Fullness")             m_gascell.setInitialFullness(textAsDouble);
        }
        else {
            int ballonetIndex = key.back() - '0';

            if (fixedKey == "x Loc")                m_ballonets[ballonetIndex].setXLocation(textAsDouble);
            if (fixedKey == "y Loc")                m_ballonets[ballonetIndex].setYLocation(textAsDouble);
            if (fixedKey == "z Loc")                m_ballonets[ballonetIndex].setZLocation(textAsDouble);
            if (fixedKey == "x Dim")                m_ballonets[ballonetIndex].setXDimension(textAsDouble);
            if (fixedKey == "y Dim")                m_ballonets[ballonetIndex].setYDimension(textAsDouble);
            if (fixedKey == "z Dim")                m_ballonets[ballonetIndex].setZDimension(textAsDouble);
            if (fixedKey == "Max Overpressure")     m_ballonets[ballonetIndex].setOverpressure(textAsDouble);
            if (fixedKey == "Valve Coefficient")    m_ballonets[ballonetIndex].setValveCoefficient(textAsDouble);
            if (fixedKey == "Fullness")             m_ballonets[ballonetIndex].setInitialFullness(textAsDouble);
            if (fixedKey == "Blower Input")         m_ballonets[ballonetIndex].setBlowerValue(textAsDouble);
        }
    }
}

void BuoyantForcesSubsystem::SetNodesFromWidgets(JSBEdit::XMLNode& parent) {    // pass in either gas_cell or ballonet node
    std::vector<JSBEdit::XMLNode> nodes;
    std::vector<JSBEdit::XMLNode> locationChildren;
    
    JSBEdit::XMLNode locationNode{*xmlptr(), "<location></location>"};
    JSBEdit::XMLNode xdimensionNode{*xmlptr(), "<x_radius></x_radius>"};
    JSBEdit::XMLNode ydimensionNode{*xmlptr(), "<y_radius></y_radius>"};
    JSBEdit::XMLNode zdimensionNode{*xmlptr(), "<z_radius></z_radius>"};
    JSBEdit::XMLNode maxoverpressureNode{*xmlptr(), "<max_ovepressure></max_overpressure>"};
    JSBEdit::XMLNode valvecoefficientNode{*xmlptr(), "<valve_coefficient></valve_coefficient>"};
    JSBEdit::XMLNode fullnessNode{*xmlptr(), "<fullness></fullness>"};

    JSBEdit::XMLNode xlocationNode{*xmlptr(), "<x></x>"};
    JSBEdit::XMLNode ylocationNode{*xmlptr(), "<y></y>"};
    JSBEdit::XMLNode zlocationNode{*xmlptr(), "<z></z>"};

    if (parent.GetName() == "gas_cell") {   // use m_gascell to access data
        // All Attributes needed
        AttributeKV gascellAttr{"type", m_gascell.gasTypeToString(m_gascell.getGasType())};
        AttributeKV locationAttr{"unit", m_gascell.unitToString(m_gascell.getLocationUnit())};
        AttributeKV dimensionAttr{"unit", m_gascell.unitToString(m_gascell.getDimensionsUnit())};
        AttributeKV overpressureAttr{"unit", m_gascell.unitToString(m_gascell.getPressureUnit())};
        AttributeKV valvecoefficientAttr{"unit", m_gascell.unitToString(m_gascell.getValveCoefficientUnit())};

        // Add Attributes and Text to Nodes
        parent.AddAttribute(gascellAttr);
        locationNode.AddAttribute(locationAttr);
        xdimensionNode.AddAttribute(dimensionAttr);
        ydimensionNode.AddAttribute(dimensionAttr);
        zdimensionNode.AddAttribute(dimensionAttr);
        maxoverpressureNode.AddAttribute(overpressureAttr);
        valvecoefficientNode.AddAttribute(valvecoefficientAttr);

        xlocationNode.SetText(std::to_string(m_gascell.getXLocation()));
        ylocationNode.SetText(std::to_string(m_gascell.getYLocation()));
        zlocationNode.SetText(std::to_string(m_gascell.getZLocation()));
        xdimensionNode.SetText(std::to_string(m_gascell.getXDimension()));
        ydimensionNode.SetText(std::to_string(m_gascell.getYDimension()));
        zdimensionNode.SetText(std::to_string(m_gascell.getZDimension()));
        maxoverpressureNode.SetText(std::to_string(m_gascell.getOverpressure()));
        valvecoefficientNode.SetText(std::to_string(m_gascell.getValveCoefficient()));
        fullnessNode.SetText(std::to_string(m_gascell.getInitialFullness()));

        // Add Nodes to Appropriate Vectors
        nodes.push_back(locationNode);
        nodes.push_back(xdimensionNode);
        nodes.push_back(ydimensionNode);
        nodes.push_back(zdimensionNode);
        nodes.push_back(maxoverpressureNode);
        nodes.push_back(valvecoefficientNode);
        nodes.push_back(fullnessNode);
        locationChildren.push_back(xlocationNode);
        locationChildren.push_back(ylocationNode);
        locationChildren.push_back(zlocationNode);

        parent.AddChildren(nodes);
        locationNode.AddChildren(locationChildren);

        // std::cout << "   DimensionsShape = " << m_gascell.unitToString(m_gascell.getDimensionsShape()) << std::endl;
        // std::cout << "   BallonetCount = " << m_gascell.getBallonetCount() << std::endl;
    } 
    else {  // use m_ballonets vector to access data
        for (auto& i : m_ballonets) {
            // All Attributes needed
            AttributeKV ballonetAttr{"type", i.gasTypeToString(i.getGasType())};
            AttributeKV locationAttr{"unit", i.unitToString(i.getLocationUnit())};
            AttributeKV dimensionAttr{"unit", i.unitToString(i.getDimensionsUnit())};
            AttributeKV overpressureAttr{"unit", i.unitToString(i.getPressureUnit())};
            AttributeKV valvecoefficientAttr{"unit", i.unitToString(i.getValveCoefficientUnit())};

            // Add Attributes and Text to Nodes
            parent.AddAttribute(ballonetAttr);
            locationNode.AddAttribute(locationAttr);
            xdimensionNode.AddAttribute(dimensionAttr);
            ydimensionNode.AddAttribute(dimensionAttr);
            zdimensionNode.AddAttribute(dimensionAttr);
            maxoverpressureNode.AddAttribute(overpressureAttr);
            valvecoefficientNode.AddAttribute(valvecoefficientAttr);

            xlocationNode.SetText(std::to_string(i.getXLocation()));
            ylocationNode.SetText(std::to_string(i.getYLocation()));
            zlocationNode.SetText(std::to_string(i.getZLocation()));
            xdimensionNode.SetText(std::to_string(i.getXDimension()));
            ydimensionNode.SetText(std::to_string(i.getYDimension()));
            zdimensionNode.SetText(std::to_string(i.getZDimension()));
            maxoverpressureNode.SetText(std::to_string(i.getOverpressure()));
            valvecoefficientNode.SetText(std::to_string(i.getValveCoefficient()));
            fullnessNode.SetText(std::to_string(i.getInitialFullness()));

            // Add Nodes to Appropriate Vectors
            nodes.push_back(locationNode);
            nodes.push_back(xdimensionNode);
            nodes.push_back(ydimensionNode);
            nodes.push_back(zdimensionNode);
            nodes.push_back(maxoverpressureNode);
            nodes.push_back(valvecoefficientNode);
            nodes.push_back(fullnessNode);
            locationChildren.push_back(xlocationNode);
            locationChildren.push_back(ylocationNode);
            locationChildren.push_back(zlocationNode);

            parent.AddChildren(nodes);
            locationNode.AddChildren(locationChildren);

            // std::cout << "   DimensionsShape = " << i.unitToString(i.getDimensionsShape()) << std::endl;
            // std::cout << "   BlowerUnit = " << i.unitToString(i.getBlowerUnit()) << std::endl;
            // std::cout << "   Blower = " << i.getBlowerValue() << std::endl;
        }
    }
}

void BuoyantForcesSubsystem::SetWidgetsFromNodes(JSBEdit::XMLNode& root, int tabIndex) {
    // std::cout << root.GetName() << std::endl;
    // std::cout << "      Gas Type: " << root.GetAttribute("type").second << std::endl;

    std::string rootName = ((tabIndex == 0) ? "gas_cell" : "ballonet");
    SetDropDownFromNode(root, rootName, "type", m_gasStringList, "Gas Type", tabIndex);
    
    auto locationNode = root.FindChild("location");
    if (locationNode) {
        auto x_locationNode = locationNode.FindChild("x");
        auto y_locationNode = locationNode.FindChild("y");
        auto z_locationNode = locationNode.FindChild("z");
        // std::cout << "         Location (unit: " << locationNode.GetAttribute("unit").second << "): "
        //           << "X=" << x_locationNode.GetText() << ", "
        //           << "Y=" << y_locationNode.GetText() << ", "
        //           << "Z=" << z_locationNode.GetText() << std::endl;

        SetDropDownFromNode(locationNode, "location", "unit", m_measurementStringList, "Location", tabIndex);
        SetEntryFromNode(x_locationNode, "x", "x Loc", tabIndex);
        SetEntryFromNode(y_locationNode, "y", "y Loc", tabIndex);
        SetEntryFromNode(z_locationNode, "z", "z Loc", tabIndex);
    }

    // Dimensions
    auto x_dimensionNode = root.FindChild("x_radius");
    if (x_dimensionNode) {
        // std::cout << "         X Dimension = " << x_dimensionNode.GetText() << " (unit = " 
        //           << x_dimensionNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(x_dimensionNode, "x_radius", "unit", m_measurementStringList, "Dimensions", tabIndex);
        SetEntryFromNode(x_dimensionNode, "x_radius", "x Dim", tabIndex);
    }

    auto y_dimensionNode = root.FindChild("y_radius");
    if (y_dimensionNode) {
        // std::cout << "         Y Dimension = " << y_dimensionNode.GetText() << " (unit = " 
        //           << y_dimensionNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(y_dimensionNode, "y_radius", "unit", m_measurementStringList, "Dimensions", tabIndex);
        SetEntryFromNode(y_dimensionNode, "y_radius", "y Dim", tabIndex);
    }

    auto z_dimensionNode = root.FindChild("z_radius");
    if (z_dimensionNode) {
        // std::cout << "         Z Dimension = " << z_dimensionNode.GetText() << " (unit = " 
        //           << z_dimensionNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(z_dimensionNode, "z_radius", "unit", m_measurementStringList, "Dimensions", tabIndex);
        SetEntryFromNode(z_dimensionNode, "z_radius", "z Dim", tabIndex);
    }

    // Other Data
    auto overpressureNode = root.FindChild("max_overpressure");
    if (overpressureNode) {
        // std::cout << "         Max Overpressure = " << overpressureNode.GetText() << " (unit = " 
        //           << overpressureNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(overpressureNode, "max_overpressure", "unit", m_pressureStringList, "Max Overpressure", tabIndex);
        SetEntryFromNode(overpressureNode, "max_overpressure", "Max Overpressure", tabIndex);
    }

    auto valveCoefficientNode = root.FindChild("valve_coefficient");
    if (valveCoefficientNode) {
        // std::cout << "         Valve Coefficient = " << valveCoefficientNode.GetText() << " (unit = "
        //           << valveCoefficientNode.GetAttribute("unit").second << ")" << std::endl;
        SetDropDownFromNode(valveCoefficientNode, "valve_coefficient", "unit", m_valveStringList, "Valve Coefficient", tabIndex);
        SetEntryFromNode(valveCoefficientNode, "valve_coefficient", "Valve Coefficient", tabIndex);
    }

    auto fullnessNode = root.FindChild("fullness");
    if (fullnessNode) {
        // std::cout << "         Fullness = " << fullnessNode.GetText() << std::endl;
        SetEntryFromNode(fullnessNode, "fullness", "Fullness", tabIndex);
    }
}

void BuoyantForcesSubsystem::SetDropDownFromNode(JSBEdit::XMLNode& node, const std::string& nodeName, 
                                                 const std::string& attributeName, const Glib::RefPtr<Gtk::StringList>& stringList, 
                                                 const std::string& dropdownLabel, int tabIndex) {
    if (node.GetName() == nodeName) {
        Glib::ustring dataRead;
        if (nodeName == "ballonet" && tabIndex == 0)     
            dataRead = attributeName;
        else                            
            dataRead = node.GetAttribute(attributeName).second;

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

void BuoyantForcesSubsystem::SetEntryFromNode(JSBEdit::XMLNode& node, const std::string& nodeName, 
                                              const std::string& entryLabel, int tabIndex) {
    if (node.GetName() == nodeName) {
        std::string dataRead = node.GetText();
        std::string keyString = entryLabel + " " + std::to_string(tabIndex);

        if (m_entries.find(keyString) != m_entries.end()) {
            m_entries[keyString]->set_text(dataRead);
        } else {
            std::cerr << "Entry with key " << keyString << " not found!" << std::endl;
        }
    }
}

void BuoyantForcesSubsystem::on_button_toggled() {
  bool enable = m_checkbutton.get_active();

  if (enable) 
    std::cout << "Buoyant Forces is ENABLED" << std::endl;
  else 
    std::cout << "Buoyant Forces is DISABLED" << std::endl;

  m_buoyantforces.setHasBuoyantForces(enable);
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
        BuildTabs(selected);
    } 
    
    else {

        if (key.find("Loc") != std::string::npos) {
            selected_string = m_measurementStringList->get_string(selected);
            Component::Unit selected_unit_type = stringToUnit(selected_string);

            if (tab_index == 0) 
                m_gascell.setLocationUnit(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setLocationUnit(selected_unit_type);
        }
        else if (key.find("Dimensions") != std::string::npos) {
            selected_string = m_measurementStringList->get_string(selected);
            Component::Unit selected_unit_type = stringToUnit(selected_string);

            if (tab_index == 0) 
                m_gascell.setDimensionsUnit(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setDimensionsUnit(selected_unit_type);
        }
        else if (key.find("Dim") != std::string::npos) {
            selected_string = m_shapeStringList->get_string(selected);
            Component::Unit selected_unit_type = stringToUnit(selected_string);

            if (tab_index == 0) 
                m_gascell.setDimensionsShape(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setDimensionsShape(selected_unit_type);
        }
        else if (key.find("Max Overpressure") != std::string::npos) {
            selected_string = m_pressureStringList->get_string(selected);
            Component::Unit selected_unit_type = stringToUnit(selected_string);

            if (tab_index == 0) 
                m_gascell.setPressureUnit(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setPressureUnit(selected_unit_type);
        }
        else if (key.find("Valve Coefficient") != std::string::npos) {
            selected_string = m_valveStringList->get_string(selected);
            Component::Unit selected_unit_type = stringToUnit(selected_string);
            
            if (tab_index == 0) 
                m_gascell.setValveCoefficientUnit(selected_unit_type);
            else 
                m_ballonets[tab_index-1].setValveCoefficientUnit(selected_unit_type);
        }
        else if (key.find("Blower Value") != std::string::npos) {
            selected_string = m_blowerStringList->get_string(selected);
            Component::Unit selected_unit_type = stringToUnit(selected_string);

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

        if (key.find("x Loc") != std::string::npos) {
            m_gascell.setXLocation(std::stod(input.raw()));
        }
        
        else if (key.find("y Loc") != std::string::npos) {
            m_gascell.setYLocation(std::stod(input.raw()));
        }
        
        else if (key.find("z Loc") != std::string::npos) {
            m_gascell.setZLocation(std::stod(input.raw()));
        }
        
        else if (key.find("x Dim") != std::string::npos) {
            m_gascell.setXDimension(std::stod(input.raw()));
        }
        
        else if (key.find("y Dim") != std::string::npos) {
            m_gascell.setYDimension(std::stod(input.raw()));
        }
        
        else if (key.find("z Dim") != std::string::npos) {
            m_gascell.setZDimension(std::stod(input.raw()));
        }
        
        else if (key.find("Max Overpressure") != std::string::npos) {
            m_gascell.setOverpressure(std::stod(input.raw()));
        }
        
        else if (key.find("Valve Coefficient") != std::string::npos) {
            m_gascell.setValveCoefficient(std::stod(input.raw()));
        }
        
        else if (key.find("Fullness") != std::string::npos) {
            m_gascell.setInitialFullness(std::stod(input.raw()));
        }
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

void BuoyantForcesSubsystem::BuildTabs(int target) 
{
    int current = m_ballonets.size();

    // Add Ballonet Objects 
    while (current < target) {
        std::cout << "Building Ballonet " << current << " Object" << std::endl;
        m_ballonets.emplace_back("Ballonet " + std::to_string(current + 1));
        m_gascell.addBallonet(m_ballonets.back());
        current++;
    }

    // Remove Ballonet Objects
    while (current > target) {
        std::cout << "Destroying Ballonet " << current << " Object" << std::endl;
        m_ballonets.pop_back();
        m_gascell.removeLastBallonet();
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
    BuildTabs(m_gascell.getBallonetCount());

  } else {
    // Input Blower Input
    AddEntry(p_grid, "Blower Input", false);
  }


  /* 


      Add Heat Widgets Here
  

  */
  
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

void BuoyantForcesSubsystem::AddEntry(Gtk::Grid& p_grid, std::string label, bool hasDDMenu) {
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

Component::Unit BuoyantForcesSubsystem::stringToUnit(const std::string& unit_string) const {
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


// Needed for Testing 
void BuoyantForcesSubsystem::on_button_clicked(const std::string& button_name) {
    std::cout << button_name << " clicked!" << std::endl;

    if (button_name == "Save") {
        // Save changes to XML file for testing
        try {
            SaveXMLData();
            std::cout << "XML data saved successfully" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error saving XML: " << e.what() << std::endl;
        }
    }

    if (button_name == "Load") {
        // Load XML data for testing
        try {
            LoadXMLData();
            std::cout << "XML data loaded successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error loading XML in Create(): " << e.what() << std::endl;
        }
    }
}