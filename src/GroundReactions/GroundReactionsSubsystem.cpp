#include <iostream>
#include <assert.h>
#include "inc/XML_api.hpp"
#include "GroundReactionsSubsystem.hpp"

GroundReactionsSubsystem::GroundReactionsSubsystem() {
    m_Name = "GroundReactions";
    std::cout << "In GroundReactionsSubsystem contructor" << std::endl; 
}

GroundReactionsSubsystem::LandingGearSetupDialog::LandingGearSetupDialog() {
    set_modal(true);

    set_title("Landing Gear Setup");
    set_default_size(715, 620);

    auto contentArea = get_content_area();

    // Create a grid for popup layout
    auto p_Grid = Gtk::make_managed<Gtk::Grid>();
    p_Grid->set_row_spacing(10);
    p_Grid->set_column_spacing(10);
    contentArea->append(*p_Grid);

    int p_row = 0;

    // Name
    auto nameLabel = Gtk::make_managed<Gtk::Label>("Name");
    auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
    nameTextbox->set_text("Name.");
    p_Grid->attach(*nameLabel, 0, p_row);
    p_Grid->attach(*nameTextbox, 1, p_row);

    // Structure
    auto structureLabel = Gtk::make_managed<Gtk::Label>("Structure");
    auto structureTextbox = Gtk::make_managed<Gtk::Entry>();
    structureTextbox->set_text("Structure.");
    p_Grid->attach(*structureLabel, 3, p_row);
    p_Grid->attach(*structureTextbox, 4, p_row++);

    // Location
    auto locationLabel = Gtk::make_managed<Gtk::Label>("Location");
    p_Grid->attach(*locationLabel, 0, p_row++);

    auto xLabel = Gtk::make_managed<Gtk::Label>("x =");
    auto xTextbox = Gtk::make_managed<Gtk::Entry>();
    xTextbox->set_text("X.");

    auto yLabel = Gtk::make_managed<Gtk::Label>("y =");
    auto yTextbox = Gtk::make_managed<Gtk::Entry>();
    yTextbox->set_text("Y.");

    auto zLabel = Gtk::make_managed<Gtk::Label>("z =");
    auto zTextbox = Gtk::make_managed<Gtk::Entry>();
    zTextbox->set_text("Z.");

    auto coordinateUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    coordinateUnitDropDown->append("IN");
    coordinateUnitDropDown->append("FT");
    coordinateUnitDropDown->append("M");
    coordinateUnitDropDown->set_active(0);

    p_Grid->attach(*xLabel, 0, p_row);
    p_Grid->attach(*xTextbox, 1, p_row);
    p_Grid->attach(*yLabel, 2, p_row);
    p_Grid->attach(*yTextbox, 3, p_row);
    p_Grid->attach(*zLabel, 4, p_row);
    p_Grid->attach(*zTextbox, 5, p_row);
    p_Grid->attach(*coordinateUnitDropDown, 6, p_row++);

    // Spring Coefficient
    auto springCoefficientLabel = Gtk::make_managed<Gtk::Label>("Spring Coefficient =");
    auto springCoefficientTextbox = Gtk::make_managed<Gtk::Entry>();
    springCoefficientTextbox->set_text("Spring Coefficient.");

    auto springCoefficientUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    springCoefficientUnitDropDown->append("LBS/FT");
    springCoefficientUnitDropDown->append("N/M");
    springCoefficientUnitDropDown->set_active(0);

    p_Grid->attach(*springCoefficientLabel, 0, p_row);
    p_Grid->attach(*springCoefficientTextbox, 1, p_row);
    p_Grid->attach(*springCoefficientUnitDropDown, 2, p_row++);

    // Damping Coefficient
    auto dampingCoefficientLabel = Gtk::make_managed<Gtk::Label>("Damping Coefficient =");
    auto dampingCoefficientTextbox = Gtk::make_managed<Gtk::Entry>();
    dampingCoefficientTextbox->set_text("Damping Coefficientt.");

    auto dampingCoefficientUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    dampingCoefficientUnitDropDown->append("LBS/FT/SEC");
    dampingCoefficientUnitDropDown->append("N/M/SEC");
    dampingCoefficientUnitDropDown->set_active(0);

    p_Grid->attach(*dampingCoefficientLabel, 0, p_row);
    p_Grid->attach(*dampingCoefficientTextbox, 1, p_row);
    p_Grid->attach(*dampingCoefficientUnitDropDown, 2, p_row++);

    // Static Friction
    auto staticFrictionLabel = Gtk::make_managed<Gtk::Label>("Static Friction =");
    auto staticFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    staticFrictionTextbox->set_text("Static Friction.");

    p_Grid->attach(*staticFrictionLabel, 0, p_row);
    p_Grid->attach(*staticFrictionTextbox, 1, p_row++);

    // Dynamic Friction
    auto dynamicFrictionLabel = Gtk::make_managed<Gtk::Label>("Dynamic Friction =");
    auto dynamicFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    dynamicFrictionTextbox->set_text("Dynamic Friction.");

    p_Grid->attach(*dynamicFrictionLabel, 0, p_row);
    p_Grid->attach(*dynamicFrictionTextbox, 1, p_row++);

    // Rolling Friction
    auto rollingFrictionLabel = Gtk::make_managed<Gtk::Label>("Rolling Friction =");
    auto rollingFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    rollingFrictionTextbox->set_text("Rolling Friction.");

    p_Grid->attach(*rollingFrictionLabel, 0, p_row);
    p_Grid->attach(*rollingFrictionTextbox, 1, p_row++);

    // Max Steer
    auto maxSteerLabel = Gtk::make_managed<Gtk::Label>("Max Steer =");
    auto maxSteerTextbox = Gtk::make_managed<Gtk::Entry>();
    maxSteerTextbox->set_text("Max Steer.");

    auto maxSteerUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    maxSteerUnitDropDown->append("DEG");
    maxSteerUnitDropDown->append("RAD");
    maxSteerUnitDropDown->set_active(0);    

    p_Grid->attach(*maxSteerLabel, 0, p_row);
    p_Grid->attach(*maxSteerTextbox, 1, p_row);
    p_Grid->attach(*maxSteerUnitDropDown, 2, p_row++);

    // Brake Group
    auto brakeGroupLabel = Gtk::make_managed<Gtk::Label>("Brake Group =");

    auto brakeGroupUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    brakeGroupUnitDropDown->append("NONE");
    brakeGroupUnitDropDown->append("LEFT");
    brakeGroupUnitDropDown->append("RIGHT");
    brakeGroupUnitDropDown->append("CENTER");
    brakeGroupUnitDropDown->append("NOSE");
    brakeGroupUnitDropDown->append("TAIL");  
    brakeGroupUnitDropDown->set_active(0);

    p_Grid->attach(*brakeGroupLabel, 0, p_row);
    p_Grid->attach(*brakeGroupUnitDropDown, 1, p_row++);

    // Retractable
    auto retractableLabel = Gtk::make_managed<Gtk::Label>("Retractable =");
    auto retractableCheckbox = Gtk::make_managed<Gtk::CheckButton>();

    p_Grid->attach(*retractableLabel, 0, p_row);
    p_Grid->attach(*retractableCheckbox, 1, p_row++);

    // Ok and Cancel Buttons
    auto okButton = Gtk::make_managed<Gtk::Button>("OK");
    okButton->signal_clicked().connect([this]() { this->close(); });
    p_Grid->attach(*okButton, 0, p_row);

    auto cancelButton = Gtk::make_managed<Gtk::Button>("Cancel");
    cancelButton->signal_clicked().connect([this]() { this->close(); });
    p_Grid->attach(*cancelButton, 1, p_row++);
}

void GroundReactionsSubsystem::Create() {
    std::cout << "in GroundReactionsSubsystem::Create" << std::endl;

    assert(xmlptr());

    // Vector for XML contact node extraction
    std::vector<JSBEdit::XMLNode> nodes = xmlptr()->GetNodes("fdm_config/ground_reactions/contact");

    // Vector for storing contact data
    std::vector<std::tuple<std::string, std::string, std::string, std::tuple<double, double, double>, std::string>> contactList;

    // XML data extraction of nodes: contact
    for (const auto& node : nodes) {
        std::string contactType = "";
        std::string contactName = "";
        std::string locationUnit = "";
        std::tuple<double, double, double> locationCoordinates = {0.0, 0.0, 0.0};
        std::string brakeGroup = " NONE ";

        // const_cast
        auto& nonConstNode = const_cast<JSBEdit::XMLNode&>(node);

        // Extraction of contact: type, name
        for (const auto& attribute : nonConstNode.GetAttributes()) {
            
            // To contactType
            if (attribute.first == "type") {
                contactType = attribute.second;
              
              // To contactName
            } else if (attribute.first == "name") {
                contactName = attribute.second;
            }
        }

        // const_cast
        auto& nonConstNodeForChildren = const_cast<JSBEdit::XMLNode&>(node);

        // XML data extraction of children: location, brake_group
        for (const auto& child : nonConstNodeForChildren.GetChildren()) {
            
            // const_cast
            auto& nonConstChild = const_cast<JSBEdit::XMLNode&>(child);

            // Extraction of location
            if (nonConstChild.GetName() == "location") {
                
                // Extraction of location: unit
                auto attribute = nonConstChild.GetAttribute("unit");
                
                // To locationUnit
                locationUnit = attribute.second; 

                // Extraction of location children: x, y, z
                for (const auto& locChild : nonConstChild.GetChildren()) {
                    
                    // const_cast
                    auto& nonConstLocChild = const_cast<JSBEdit::XMLNode&>(locChild);
                    
                    // To locationCoordinates
                    if (nonConstLocChild.GetName() == "x") {
                        std::get<0>(locationCoordinates) = std::stod(nonConstLocChild.GetText());
                    } else if (nonConstLocChild.GetName() == "y") {
                        std::get<1>(locationCoordinates) = std::stod(nonConstLocChild.GetText());
                    } else if (nonConstLocChild.GetName() == "z") {
                        std::get<2>(locationCoordinates) = std::stod(nonConstLocChild.GetText());
                    }
                }
              
              // Extraction of brake_group
            } else if (nonConstChild.GetName() == "brake_group") {
                
                // To brakeGroup
                brakeGroup = nonConstChild.GetText();
            }
        }

        // Extracted data to contactList vector 
        contactList.push_back(std::make_tuple(contactType, contactName, locationUnit, locationCoordinates, brakeGroup));
    }

    // Main grid
    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    // ListBox for contacts
    auto m_ContactListBox = Gtk::make_managed<Gtk::ListBox>();
    m_ContactListBox->set_selection_mode(Gtk::SelectionMode::SINGLE);

    // contactList vector tuples to m_ContactListBox rows
    for (const auto& contact : contactList) {
        auto contactType = std::get<0>(contact);
        auto contactName = std::get<1>(contact);
        auto locationUnit = std::get<2>(contact);
        auto locationCoordinates = std::get<3>(contact);
        auto brakeGroup = std::get<4>(contact);

        auto labelText = contactName + " (" + contactType + ") at point [" +
            std::to_string(std::get<0>(locationCoordinates)) + ", " +
            std::to_string(std::get<1>(locationCoordinates)) + ", " +
            std::to_string(std::get<2>(locationCoordinates)) + "] in " + locationUnit + " (in" +
            brakeGroup + "brake group)";

        auto label = Gtk::make_managed<Gtk::Label>(labelText);
        auto row = Gtk::make_managed<Gtk::ListBoxRow>();
        row->set_child(*label);
        m_ContactListBox->append(*row);
    }

    // Initial m_ContactListBox row selection clear
    Glib::signal_idle().connect_once([m_ContactListBox]() {
        m_ContactListBox->unselect_all();
    });

    // GestureClick for m_ContactListBox row double-click detection
    auto gesture = Gtk::GestureClick::create();
    gesture->signal_released().connect([this, m_ContactListBox](int n_press, double, double) {
        if (n_press == 2) {
            auto row = m_ContactListBox->get_selected_row();
            if (row) {
                auto label = dynamic_cast<Gtk::Label*>(row->get_child());
                if (label) {
                    auto landingGearDialog = new LandingGearSetupDialog();
                    landingGearDialog->show();
                }
            }
        }
    });
    m_ContactListBox->add_controller(gesture);

    // m_ContactListBox to grid
    m_Grid.attach(*m_ContactListBox, 0, 0);

    // Keep track of rows
    //int row = 1; // unused variable 
}
