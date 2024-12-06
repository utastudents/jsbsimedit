#include <iostream>
#include "ExternalReactionsSubsystem.hpp"

ExternalReactionsSubsystem::ExternalReactionsSubsystem() {
    m_Name = "External Reactions";
    //std::cout << "In ExternalReactionsSubsystem constructor" << std::endl;
    m_forceCount = 2;
}

void ExternalReactionsSubsystem::Create() {
    std::cout << "In ExternalReactionsSubsystem::Create" << std::endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);
    int row = 1;

    m_notebook.set_margin(10);
    m_notebook.set_expand();
    m_Grid.attach(m_notebook, 0, 0);

    // Adding "Force 1" tab
    m_pages.push_back(std::make_unique<Gtk::Grid>());
    m_notebook.append_page(*m_pages.back(), "Force 1");

    // Adding "Force 2" tab
    m_pages.push_back(std::make_unique<Gtk::Grid>());
    m_notebook.append_page(*m_pages.back(), "Force 2");

    m_nameTextbox = Gtk::make_managed<Gtk::Entry>();
    m_nameTextbox->set_text("");
    m_Grid.attach(*m_nameTextbox, 1, row);

    auto newForceButton = Gtk::make_managed<Gtk::Button>("Add Force");
    newForceButton->set_hexpand(false);
    newForceButton->set_vexpand(false);
    newForceButton->set_margin(5);

    newForceButton->set_halign(Gtk::Align::START);
    newForceButton->set_valign(Gtk::Align::START);
    
    newForceButton->signal_clicked().connect([this]() {
        std::string forceName = m_nameTextbox->get_text();
        
        if(forceName.empty()) {
            forceName = "Force " + std::to_string(++m_forceCount);
        }
        
        m_pages.push_back(std::make_unique<Gtk::Grid>());
        m_notebook.append_page(*m_pages.back(), forceName);
        m_nameTextbox->set_text("");
    });
    m_Grid.attach(*newForceButton, 1, 0);

    // Force Name Input
    auto nameLabel = Gtk::make_managed<Gtk::Label>("FORCE NAME");
    m_Grid.attach(*nameLabel, 0, row);

    // Force Type Dropdown
    auto typeLabel = Gtk::make_managed<Gtk::Label>("FORCE TYPE");
    auto typeDropDownList = Gtk::make_managed<Gtk::ComboBoxText>();
    typeDropDownList->append("Push-back");
    typeDropDownList->append("Hook");
    typeDropDownList->append("Gravity");
    typeDropDownList->set_active(0); // Default to "Push-back"
    m_Grid.attach(*typeLabel, 3, row);
    m_Grid.attach(*typeDropDownList, 4, row);

    // Force Metrics Dropdown
    auto metricLabel = Gtk::make_managed<Gtk::Label>("METRIC");
    auto metricDropDownList = Gtk::make_managed<Gtk::ComboBoxText>();
    metricDropDownList->append("Inches");
    metricDropDownList->append("Meters");
    metricDropDownList->append("Feet");
    metricDropDownList->set_active(0); // Default to "Inches"
    m_Grid.attach(*metricLabel, 5, row);
    m_Grid.attach(*metricDropDownList, 6, row);

    // Location Input Fields
    auto locLabel = Gtk::make_managed<Gtk::Label>("LOCATION");
    auto locXTextbox = Gtk::make_managed<Gtk::Entry>();
    auto locYTextbox = Gtk::make_managed<Gtk::Entry>();
    auto locZTextbox = Gtk::make_managed<Gtk::Entry>();
    locXTextbox->set_placeholder_text("X");
    locYTextbox->set_placeholder_text("Y");
    locZTextbox->set_placeholder_text("Z");
    m_Grid.attach(*locLabel, 0, row + 1);
    m_Grid.attach(*locXTextbox, 1, row + 1);
    m_Grid.attach(*locYTextbox, 2, row + 1);
    m_Grid.attach(*locZTextbox, 3, row + 1);

    // Direction Input Fields
    auto dirLabel = Gtk::make_managed<Gtk::Label>("DIRECTION");
    auto dirXTextbox = Gtk::make_managed<Gtk::Entry>();
    auto dirYTextbox = Gtk::make_managed<Gtk::Entry>();
    auto dirZTextbox = Gtk::make_managed<Gtk::Entry>();
    dirXTextbox->set_placeholder_text("X");
    dirYTextbox->set_placeholder_text("Y");
    dirZTextbox->set_placeholder_text("Z");
    m_Grid.attach(*dirLabel, 0, row + 2);
    m_Grid.attach(*dirXTextbox, 1, row + 2);
    m_Grid.attach(*dirYTextbox, 2, row + 2);
    m_Grid.attach(*dirZTextbox, 3, row + 2);

    // Frame Dropdown
    auto frameLabel = Gtk::make_managed<Gtk::Label>("FRAME");
    auto frameDropDownList = Gtk::make_managed<Gtk::ComboBoxText>();
    frameDropDownList->append("BODY");
    frameDropDownList->append("LOCAL");
    frameDropDownList->append("WIND");
    frameDropDownList->set_active(0); // Default to "BODY"
    m_Grid.attach(*frameLabel, 0, row + 3);
    m_Grid.attach(*frameDropDownList, 1, row + 3);

    // Connect Force Type Dropdown
    typeDropDownList->signal_changed().connect([ typeDropDownList, locXTextbox, locYTextbox, locZTextbox, dirXTextbox, dirYTextbox, dirZTextbox]() {
        std::string selectedType = typeDropDownList->get_active_text();
        if (selectedType == "Push-back") {
            locXTextbox->set_text("1.0");
            locYTextbox->set_text("0.0");
            locZTextbox->set_text("0.0");
            dirXTextbox->set_text("-2.0");
            dirYTextbox->set_text("0.0");
            dirZTextbox->set_text("-1.0");
        } else if (selectedType == "Hook") {
            locXTextbox->set_text("0.5");
            locYTextbox->set_text("0.5");
            locZTextbox->set_text("0.5");
            dirXTextbox->set_text("2.0");
            dirYTextbox->set_text("1.0");
            dirZTextbox->set_text("-1.0");
        }
        // Additional force types can be added here
    });
}
