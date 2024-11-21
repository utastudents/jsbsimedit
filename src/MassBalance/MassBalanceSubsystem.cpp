#include <iostream>
#include "MassBalanceSubsystem.hpp"
#include "Location.hpp" 

MassBalanceSubsystem::MassBalanceSubsystem() {
    m_Name = "Mass Balance";
    std::cout << "In MassBalanceSubsystem constructor" << std::endl; 
}

void MassBalanceSubsystem::Create() {
    std::cout << "In MassBalanceSubsystem::Create" << std::endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    // empty weight label
    auto label_empty_weight = Gtk::make_managed<Gtk::Label>("Empty Weight:");
    m_Grid.attach(*label_empty_weight, 1, 1, 1, 1);
    label_empty_weight->set_halign(Gtk::Align::CENTER);

    //location label
    auto label_location = Gtk::make_managed<Gtk::Label>("Location:");
    m_Grid.attach(*label_location, 1, 2, 1, 1);
    label_location->set_halign(Gtk::Align::CENTER);

    // box to view weight
    auto entry_empty_weight = Gtk::make_managed<Gtk::Entry>();
    entry_empty_weight->set_editable(false);
    m_Grid.attach(*entry_empty_weight, 2, 1, 1, 1);

    // dropdown to choose lbs or kg for empty mass
    auto combo_units = Gtk::make_managed<Gtk::ComboBoxText>();
    combo_units->append("lbs");
    combo_units->append("kgs");
    combo_units->set_active(0); // Default to "lbs"
    m_Grid.attach(*combo_units, 3, 1, 1, 1);

    
    auto pBoxX = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    auto pBoxY = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    auto pBoxZ = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);

    Gtk::Label xLabel("X: \t test");
    Gtk::Label yLabel("Y: \t test");
    Gtk::Label zLabel("Z: \t test");

    pBoxX->append(xLabel);
    pBoxY->append(yLabel);
    pBoxZ->append(zLabel);

    m_Grid.attach(*pBoxX, 0, 10, 1, 1);
    m_Grid.attach(*pBoxY, 1, 10, 1, 1);
    m_Grid.attach(*pBoxZ, 2, 10, 1, 1);
}
