#include <iostream>
#include <assert.h>
#include "inc/XML_api.hpp"
#include "GroundReactionsSubsystem.hpp"

GroundReactionsSubsystem::GroundReactionsSubsystem() {
    m_Name = "GroundReactions";
    //std::cout << "In GroundReactionsSubsystem contructor" << std::endl; 
}

GroundReactionsSubsystem::LandingGearSetupDialog::LandingGearSetupDialog(
    const std::string& contactName, const std::string& contactType, 
    const std::tuple<std::string, std::string, std::string>& locationCoordinates, const std::string& locationUnit, 
    const std::string& springCoefficient, const std::string& springCoefficientUnit, 
    const std::string& dampingCoefficient, const std::string& dampingCoefficientUnit, 
    const std::string& staticFriction, 
    const std::string& dynamicFriction, 
    const std::string& rollingFriction, 
    const std::string& maxSteer, const std::string& maxSteerUnit, 
    const std::string& brakeGroup, 
    const std::string& retractable
) {

    set_modal(true);

    set_title("Landing Gear Setup");
    set_default_size(1050, 620);

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
    nameTextbox->set_text(contactName);  // Populate with contactName
    p_Grid->attach(*nameLabel, 0, p_row);
    p_Grid->attach(*nameTextbox, 1, p_row);

    // Structure
    auto structureLabel = Gtk::make_managed<Gtk::Label>("Structure");
    auto structureTextbox = Gtk::make_managed<Gtk::Entry>();
    structureTextbox->set_text(contactType);  // Populate with contactType
    p_Grid->attach(*structureLabel, 3, p_row);
    p_Grid->attach(*structureTextbox, 4, p_row++);

    // Location
    auto locationLabel = Gtk::make_managed<Gtk::Label>("Location");
    p_Grid->attach(*locationLabel, 0, p_row++);

    auto xLabel = Gtk::make_managed<Gtk::Label>("x =");
    auto xTextbox = Gtk::make_managed<Gtk::Entry>();
    xTextbox->set_text(std::get<0>(locationCoordinates));  // Populate with x-coordinate

    auto yLabel = Gtk::make_managed<Gtk::Label>("y =");
    auto yTextbox = Gtk::make_managed<Gtk::Entry>();
    yTextbox->set_text(std::get<1>(locationCoordinates));  // Populate with y-coordinate

    auto zLabel = Gtk::make_managed<Gtk::Label>("z =");
    auto zTextbox = Gtk::make_managed<Gtk::Entry>();
    zTextbox->set_text(std::get<2>(locationCoordinates));  // Populate with z-coordinate

    auto coordinateUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    coordinateUnitDropDown->append("IN");
    coordinateUnitDropDown->append("FT");
    coordinateUnitDropDown->append("M");
    coordinateUnitDropDown->set_active_text(locationUnit);  // Set to locationUnit

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
    springCoefficientTextbox->set_text(springCoefficient); // Populate with springCoefficient

    auto springCoefficientUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    springCoefficientUnitDropDown->append("LBS/FT");
    springCoefficientUnitDropDown->append("N/M");
    springCoefficientUnitDropDown->set_active_text(springCoefficientUnit); // Set to springCoefficientUnit

    p_Grid->attach(*springCoefficientLabel, 0, p_row);
    p_Grid->attach(*springCoefficientTextbox, 1, p_row);
    p_Grid->attach(*springCoefficientUnitDropDown, 2, p_row++);

    // Damping Coefficient
    auto dampingCoefficientLabel = Gtk::make_managed<Gtk::Label>("Damping Coefficient =");
    auto dampingCoefficientTextbox = Gtk::make_managed<Gtk::Entry>();
    dampingCoefficientTextbox->set_text(dampingCoefficient); // Populate with dampingCoefficient

    auto dampingCoefficientUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    dampingCoefficientUnitDropDown->append("LBS/FT/SEC");
    dampingCoefficientUnitDropDown->append("N/M/SEC");
    dampingCoefficientUnitDropDown->set_active_text(dampingCoefficientUnit); // Set to dampingCoefficientUnit

    p_Grid->attach(*dampingCoefficientLabel, 0, p_row);
    p_Grid->attach(*dampingCoefficientTextbox, 1, p_row);
    p_Grid->attach(*dampingCoefficientUnitDropDown, 2, p_row++);

    // Static Friction
    auto staticFrictionLabel = Gtk::make_managed<Gtk::Label>("Static Friction =");
    auto staticFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    staticFrictionTextbox->set_text(staticFriction); // Populate with staticFriction

    p_Grid->attach(*staticFrictionLabel, 0, p_row);
    p_Grid->attach(*staticFrictionTextbox, 1, p_row++);

    // Dynamic Friction
    auto dynamicFrictionLabel = Gtk::make_managed<Gtk::Label>("Dynamic Friction =");
    auto dynamicFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    dynamicFrictionTextbox->set_text(dynamicFriction); // Populate with dynamicFriction

    p_Grid->attach(*dynamicFrictionLabel, 0, p_row);
    p_Grid->attach(*dynamicFrictionTextbox, 1, p_row++);

    // Rolling Friction
    auto rollingFrictionLabel = Gtk::make_managed<Gtk::Label>("Rolling Friction =");
    auto rollingFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    rollingFrictionTextbox->set_text(rollingFriction); // Populate with rollingFriction

    p_Grid->attach(*rollingFrictionLabel, 0, p_row);
    p_Grid->attach(*rollingFrictionTextbox, 1, p_row++);

    // Max Steer
    auto maxSteerLabel = Gtk::make_managed<Gtk::Label>("Max Steer =");
    auto maxSteerTextbox = Gtk::make_managed<Gtk::Entry>();
    maxSteerTextbox->set_text(maxSteer); // Populate with maxSteer

    auto maxSteerUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    maxSteerUnitDropDown->append("DEG");
    maxSteerUnitDropDown->append("RAD");
    maxSteerUnitDropDown->set_active_text(maxSteerUnit); // Set to maxSteerUnit

    p_Grid->attach(*maxSteerLabel, 0, p_row);
    p_Grid->attach(*maxSteerTextbox, 1, p_row);
    p_Grid->attach(*maxSteerUnitDropDown, 2, p_row++);

    // Brake Group
    auto brakeGroupLabel = Gtk::make_managed<Gtk::Label>("Brake Group =");

    auto brakeGroupUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    brakeGroupUnitDropDown->append(" NONE ");
    brakeGroupUnitDropDown->append(" LEFT ");
    brakeGroupUnitDropDown->append(" RIGHT ");
    brakeGroupUnitDropDown->append(" CENTER ");
    brakeGroupUnitDropDown->append(" NOSE ");
    brakeGroupUnitDropDown->append(" TAIL ");
    brakeGroupUnitDropDown->set_active_text(brakeGroup);  // Set to brakeGroup

    p_Grid->attach(*brakeGroupLabel, 0, p_row);
    p_Grid->attach(*brakeGroupUnitDropDown, 1, p_row++);

    // Retractable
    auto retractableLabel = Gtk::make_managed<Gtk::Label>("Retractable =");
    auto retractableCheckbox = Gtk::make_managed<Gtk::CheckButton>();
    if (retractable == "1") {
        retractableCheckbox->set_active(TRUE);
    }
    else {
        retractableCheckbox->set_active(FALSE);
    }

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

    JSBEdit::XMLDoc doc;
    doc.LoadFileAndParse("../../../data/aircraft/f16/f16.xml");

    // Vector for XML contact node extraction
    std::vector<JSBEdit::XMLNode> nodes = doc.GetNodes("fdm_config/ground_reactions/contact");

    // Vector for storing contact data
    std::vector<std::tuple<std::string, std::string, std::tuple<std::string, std::string, std::string>, std::string, std::string, std::string, std::string, 
                           std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string>> contactList;

    // XML data extraction of nodes: contact
    for (const auto& node : nodes) {
        std::string contactName = "";
        std::string contactType = "";
        std::tuple<std::string, std::string, std::string> locationCoordinates = {"0.0", "0.0", "0.0"};
        std::string locationUnit = "IN";
        std::string springCoefficient = " 0 ";
        std::string springCoefficientUnit = "LBS/FT";
        std::string dampingCoefficient = " 0 ";
        std::string dampingCoefficientUnit = "LBS/FT/SEC";
        std::string staticFriction = " 0.00 ";
        std::string dynamicFriction = " 0.00 ";
        std::string rollingFriction = " 0.00 ";
        std::string maxSteer = " 0.0 ";
        std::string maxSteerUnit = "DEG";
        std::string brakeGroup = " NONE ";
        std::string retractable = "0";

        // const_cast
        auto& nonConstNode = const_cast<JSBEdit::XMLNode&>(node);

        // Extraction of contact: type, name
        for (const auto& attribute : nonConstNode.GetAttributes()) {
            if (attribute.first == "type") {
                contactType = attribute.second;
            } else if (attribute.first == "name") {
                contactName = attribute.second;
            }
        }

        // XML data extraction of children
        for (const auto& child : nonConstNode.GetChildren()) {
            auto& nonConstChild = const_cast<JSBEdit::XMLNode&>(child);

            // Extraction of location
            if (nonConstChild.GetName() == "location") {
                
                // Extraction of location: unit
                auto attribute = nonConstChild.GetAttribute("unit");
                locationUnit = attribute.second;

                // Extraction of location children: x, y, z
                for (const auto& locChild : nonConstChild.GetChildren()) {
                    auto& nonConstLocChild = const_cast<JSBEdit::XMLNode&>(locChild);
                    if (nonConstLocChild.GetName() == "x") {
                        std::get<0>(locationCoordinates) = nonConstLocChild.GetText();
                    } else if (nonConstLocChild.GetName() == "y") {
                        std::get<1>(locationCoordinates) = nonConstLocChild.GetText();
                    } else if (nonConstLocChild.GetName() == "z") {
                        std::get<2>(locationCoordinates) = nonConstLocChild.GetText();
                    }
                }
            
            // Extraction of spring_coeff
            } else if (nonConstChild.GetName() == "spring_coeff") {
                springCoefficient = nonConstChild.GetText();
                
                // Extraction of spring_coeff: unit
                auto attribute = nonConstChild.GetAttribute("unit");
                springCoefficientUnit = attribute.second;
            
            // Extraction of damping_coeff
            } else if (nonConstChild.GetName() == "damping_coeff") {
                dampingCoefficient = nonConstChild.GetText();

                // Extraction of damping_coeff: unit
                auto attribute = nonConstChild.GetAttribute("unit");
                dampingCoefficientUnit = attribute.second;
            
            // Extraction of static_friction
            } else if (nonConstChild.GetName() == "static_friction") {
                staticFriction = nonConstChild.GetText();
            
            // Extraction of dynamic_friction
            } else if (nonConstChild.GetName() == "dynamic_friction") {
                dynamicFriction = nonConstChild.GetText();
            
            // Extraction of rolling_friction
            } else if (nonConstChild.GetName() == "rolling_friction") {
                rollingFriction = nonConstChild.GetText();
            
            // Extraction of max_steer
            } else if (nonConstChild.GetName() == "max_steer") {
                maxSteer = nonConstChild.GetText();

                // Extraction of max_steer: unit
                auto attribute = nonConstChild.GetAttribute("unit");
                maxSteerUnit = attribute.second;
            
            //Extraction of brake_group
            } else if (nonConstChild.GetName() == "brake_group") {
                brakeGroup = nonConstChild.GetText();
            
            // Extraction of retractable
            } else if (nonConstChild.GetName() == "retractable") {
                retractable = nonConstChild.GetText();
            }
        }

        // Add extracted data to contactList vector
        contactList.push_back(std::make_tuple(
            contactName, contactType, 
            locationCoordinates, locationUnit, 
            springCoefficient, springCoefficientUnit, 
            dampingCoefficient, dampingCoefficientUnit, 
            staticFriction, 
            dynamicFriction, 
            rollingFriction, 
            maxSteer, maxSteerUnit, 
            brakeGroup, 
            retractable
        ));
    }

    // Main grid
    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    // ListBox for contacts
    auto m_ContactListBox = Gtk::make_managed<Gtk::ListBox>();
    m_ContactListBox->set_halign(Gtk::Align::FILL);
    m_ContactListBox->set_hexpand(true);
    m_ContactListBox->set_selection_mode(Gtk::SelectionMode::SINGLE);

    // contactList vector tuples to m_ContactListBox rows
    for (const auto& contact : contactList) {
        auto contactName = std::get<0>(contact);
        auto contactType = std::get<1>(contact);
        auto locationCoordinates = std::get<2>(contact);
        auto locationUnit = std::get<3>(contact);
        auto springCoefficient = std::get<4>(contact);
        auto springCoefficientUnit = std::get<5>(contact);
        auto dampingCoefficient = std::get<6>(contact);
        auto dampingCoefficientUnit = std::get<7>(contact);
        auto staticFriction = std::get<8>(contact);
        auto dynamicFriction = std::get<9>(contact);
        auto rollingFriction = std::get<10>(contact);
        auto maxSteer = std::get<11>(contact);
        auto maxSteerUnit = std::get<12>(contact);
        auto brakeGroup = std::get<13>(contact);
        auto retractable = std::get<14>(contact);

        auto labelText = contactName + " (" + contactType + ") at point [" +
                         std::get<0>(locationCoordinates) + ", " +
                         std::get<1>(locationCoordinates) + ", " +
                         std::get<2>(locationCoordinates) + "] in " + locationUnit + " (in" +
                         brakeGroup + "brake group)";

        auto label = Gtk::make_managed<Gtk::Label>(labelText);
        label->set_halign(Gtk::Align::START);
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
    gesture->signal_released().connect([this, m_ContactListBox, contactList](int n_press, double, double) {
        if (n_press == 2) {
            auto row = m_ContactListBox->get_selected_row();
            auto index = row->get_index();

            // Contact details for dialog
            const auto& contact = contactList[index];
            const auto& contactName = std::get<0>(contact);
            const auto& contactType = std::get<1>(contact);
            const auto& locationCoordinates = std::get<2>(contact);
            const auto& locationUnit = std::get<3>(contact);
            const auto& springCoefficient = std::get<4>(contact);
            const auto& springCoefficientUnit = std::get<5>(contact);
            const auto& dampingCoefficient = std::get<6>(contact);
            const auto& dampingCoefficientUnit = std::get<7>(contact);
            const auto& staticFriction = std::get<8>(contact);
            const auto& dynamicFriction = std::get<9>(contact);
            const auto& rollingFriction = std::get<10>(contact);
            const auto& maxSteer = std::get<11>(contact);
            const auto& maxSteerUnit = std::get<12>(contact);
            const auto& brakeGroup = std::get<13>(contact);
            const auto& retractable = std::get<14>(contact);

            auto landingGearDialog = Gtk::make_managed<LandingGearSetupDialog>(
                contactName, contactType, 
                locationCoordinates, locationUnit, 
                springCoefficient, springCoefficientUnit, 
                dampingCoefficient, dampingCoefficientUnit, 
                staticFriction, 
                dynamicFriction, 
                rollingFriction, 
                maxSteer, maxSteerUnit, 
                brakeGroup, 
                retractable
            );
            landingGearDialog->show();
        }
    });
    m_ContactListBox->add_controller(gesture);

    // m_ContactListBox to grid
    m_Grid.attach(*m_ContactListBox, 0, 0);

    // Keep track of rows
    //int row = 1; // unused variable for now
}
