#include <iostream>
#include "ExternalReactionsSubsystem.hpp"

ExternalReactionsSubsystem::ExternalReactionsSubsystem() {
    m_Name = "External Reactions";
    std::cout << "In ExternalReactionsSubsystem constructor" << std::endl;
}

void ExternalReactionsSubsystem::Create() {
    std::cout << "In ExternalReactionsSubsystem::Create" << std::endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);
    int row = 1;

    m_notebook.set_margin(10);
    m_notebook.set_expand();
    m_Grid.attach(m_notebook, 0, 0);
    m_pages.push_back(std::make_unique<Gtk::Grid>());
    m_notebook.append_page(*m_pages.back(), "Force 1");

    // Force Name takes in a user input string
    auto nameLabel = Gtk::make_managed<Gtk::Label>("FORCE NAME");
    auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
    nameTextbox->set_text("");
    m_Grid.attach(*nameLabel, 0, row);
    m_Grid.attach(*nameTextbox, 1, row);

    // Force Type dropdown window
    auto typeLabel = Gtk::make_managed<Gtk::Label>("FORCE TYPE");
    auto typeDropDownList = Gtk::make_managed<Gtk::ComboBoxText>();
    typeDropDownList->append("Push-back");
    typeDropDownList->append("Hook");
    typeDropDownList->append("Gravity");
    typeDropDownList->set_active(0); // Set default value
    m_Grid.attach(*typeLabel, 3, row);
    m_Grid.attach(*typeDropDownList, 4, row);

    // Attach to force object when selected
    typeDropDownList->signal_changed().connect([this, typeDropDownList]() {
        std::string selectedType = typeDropDownList->get_active_text();
        if (selectedType == "Push-back") {
            m_currentForce = Force(Force::forceVector(-2.98081, 0.0, -1.9683), Force::forceVector(1, 0, 0));
        } else if (selectedType == "Hook") {
            m_currentForce = Force(Force::forceVector(100.669, 0.0, -28.818), Force::forceVector(-0.9995, 0.0, 0.01));
        }
        // Additional types can be added here
    });

    // Frame dropdown window
    auto frameLabel = Gtk::make_managed<Gtk::Label>("FRAME");
    auto frameDropDownList = Gtk::make_managed<Gtk::ComboBoxText>();
    frameDropDownList->append("BODY");
    frameDropDownList->append("LOCAL");
    frameDropDownList->append("WIND");
    m_Grid.attach(*frameLabel, 3, row + 2);
    m_Grid.attach(*frameDropDownList, 4, row + 2);

    // Location and Direction fields as before...
}
