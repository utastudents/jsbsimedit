#include <iostream>
#include "GroundReactionsSubsystem.hpp"

GroundReactionsSubsystem::GroundReactionsSubsystem() {
    m_Name = "GroundReactions";
    std::cout << "In GroundReactionsSubsystem contructor" << std::endl; 
}

void GroundReactionsSubsystem::Create() {
    std :: cout << "in GroundReactionsSubsystem::Create" << std :: endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    // Keep track of rows
    int row = 0;

    // Name
    auto nameLabel = Gtk::make_managed<Gtk::Label>("Name");
    auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
    nameTextbox->set_text("Name.");
    m_Grid.attach(*nameLabel, 0, row);
    m_Grid.attach(*nameTextbox, 1, row);

    // Structure
    auto structureLabel = Gtk::make_managed<Gtk::Label>("Structure");
    auto structureTextbox = Gtk::make_managed<Gtk::Entry>();
    structureTextbox->set_text("Structure.");
    m_Grid.attach(*structureLabel, 3, row);
    m_Grid.attach(*structureTextbox, 4, row++);

    // Location
    auto locationLabel = Gtk::make_managed<Gtk::Label>("Location");
    m_Grid.attach(*locationLabel, 0, row++);

    // Coordinates
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

    m_Grid.attach(*xLabel, 0, row);
    m_Grid.attach(*xTextbox, 1, row);
    m_Grid.attach(*yLabel, 2, row);
    m_Grid.attach(*yTextbox, 3, row);
    m_Grid.attach(*zLabel, 4, row);
    m_Grid.attach(*zTextbox, 5, row);
    m_Grid.attach(*coordinateUnitDropDown, 6, row++);

    // Spring Coefficient
    auto springCoefficientLabel = Gtk::make_managed<Gtk::Label>("Spring Coefficient =");
    auto springCoefficientTextbox = Gtk::make_managed<Gtk::Entry>();
    springCoefficientTextbox->set_text("Spring Coefficient.");

    auto springCoefficientUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    springCoefficientUnitDropDown->append("LBS/FT");
    springCoefficientUnitDropDown->append("N/M");
    springCoefficientUnitDropDown->set_active(0);

    m_Grid.attach(*springCoefficientLabel, 0, row);
    m_Grid.attach(*springCoefficientTextbox, 1, row);
    m_Grid.attach(*springCoefficientUnitDropDown, 2, row++);

    // Damping Coefficient
    auto dampingCoefficientLabel = Gtk::make_managed<Gtk::Label>("Damping Coefficient =");
    auto dampingCoefficientTextbox = Gtk::make_managed<Gtk::Entry>();
    dampingCoefficientTextbox->set_text("Damping Coefficientt.");

    auto dampingCoefficientUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    dampingCoefficientUnitDropDown->append("LBS/FT/SEC");
    dampingCoefficientUnitDropDown->append("N/M/SEC");
    dampingCoefficientUnitDropDown->set_active(0);

    m_Grid.attach(*dampingCoefficientLabel, 0, row);
    m_Grid.attach(*dampingCoefficientTextbox, 1, row);
    m_Grid.attach(*dampingCoefficientUnitDropDown, 2, row++);

    // Static Friction
    auto staticFrictionLabel = Gtk::make_managed<Gtk::Label>("Static Friction =");
    auto staticFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    staticFrictionTextbox->set_text("Static Friction.");

    m_Grid.attach(*staticFrictionLabel, 0, row);
    m_Grid.attach(*staticFrictionTextbox, 1, row++);

    // Dynamic Friction
    auto dynamicFrictionLabel = Gtk::make_managed<Gtk::Label>("Dynamic Friction =");
    auto dynamicFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    dynamicFrictionTextbox->set_text("Dynamic Friction.");

    m_Grid.attach(*dynamicFrictionLabel, 0, row);
    m_Grid.attach(*dynamicFrictionTextbox, 1, row++);

    // Rolling Friction
    auto rollingFrictionLabel = Gtk::make_managed<Gtk::Label>("Rolling Friction =");
    auto rollingFrictionTextbox = Gtk::make_managed<Gtk::Entry>();
    rollingFrictionTextbox->set_text("Rolling Friction.");

    m_Grid.attach(*rollingFrictionLabel, 0, row);
    m_Grid.attach(*rollingFrictionTextbox, 1, row++);

    // Max Stear
    auto maxStearLabel = Gtk::make_managed<Gtk::Label>("Max Stear =");
    auto maxStearTextbox = Gtk::make_managed<Gtk::Entry>();
    maxStearTextbox->set_text("Max Stear.");

    auto maxStearUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    maxStearUnitDropDown->append("DEG");
    maxStearUnitDropDown->append("RAD");
    maxStearUnitDropDown->set_active(0);    

    m_Grid.attach(*maxStearLabel, 0, row);
    m_Grid.attach(*maxStearTextbox, 1, row);
    m_Grid.attach(*maxStearUnitDropDown, 2, row++);

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

    m_Grid.attach(*brakeGroupLabel, 0, row);
    m_Grid.attach(*brakeGroupUnitDropDown, 1, row++);

    // Retractable
    auto retractableLabel = Gtk::make_managed<Gtk::Label>("Retractable =");
    auto retractableCheckbox = Gtk::make_managed<Gtk::CheckButton>();

    m_Grid.attach(*retractableLabel, 0, row);
    m_Grid.attach(*retractableCheckbox, 1, row++);

    // Ok and Cancel Buttons
    auto Ok = Glib::ustring::compose("OK");
    auto OkButton = Gtk::make_managed<Gtk::ToggleButton>(Ok);
    m_Grid.attach(*OkButton, 0, row);

    auto Cancel = Glib::ustring::compose("Cancel");
    auto CancelButton = Gtk::make_managed<Gtk::ToggleButton>(Cancel);
    m_Grid.attach(*CancelButton, 2, row);
}
