#include <iostream>
#include "MassBalanceSubsystem.hpp"
#include "Location.hpp" // Include location class

MassBalanceSubsystem::MassBalanceSubsystem() {
    m_Name = "Mass Balance";
    std::cout << "In MassBalanceSubsystem constructor" << std::endl; 
}

void MassBalanceSubsystem::Create() {
    std::cout << "In MassBalanceSubsystem::Create" << std::endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    // Adding three Gtk::Box widgets for x, y, and z values
    auto pBoxX = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    auto pBoxY = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    auto pBoxZ = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);

    // Add labels to display x, y, z values (assuming x, y, z are stored in a location object)
    Location loc; // Create a location object to hold x, y, z values
    Gtk::Label xLabel("X: " + std::to_string(loc.getX()));
    Gtk::Label yLabel("Y: " + std::to_string(loc.getY()));
    Gtk::Label zLabel("Z: " + std::to_string(loc.getZ()));

    // Attach the labels to each corresponding box using append
    pBoxX->append(xLabel);
    pBoxY->append(yLabel);
    pBoxZ->append(zLabel);

    // Attach these boxes to the grid layout
    m_Grid.attach(*pBoxX, 0, 10, 1, 1);
    m_Grid.attach(*pBoxY, 1, 10, 1, 1);
    m_Grid.attach(*pBoxZ, 2, 10, 1, 1);
}
