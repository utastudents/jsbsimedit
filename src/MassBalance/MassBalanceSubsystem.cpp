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

    //3 gtk boxes for x,y,z
    auto pBoxX = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    auto pBoxY = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    auto pBoxZ = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);

    
    //Location loc; <- some kind of naming conflict with this 
    Gtk::Label xLabel("X: \t test");
    Gtk::Label yLabel("Y: \t test");
    Gtk::Label zLabel("Z: \t test");

    //label boxes
    pBoxX->append(xLabel);
    pBoxY->append(yLabel);
    pBoxZ->append(zLabel);

    //attach to grid
    m_Grid.attach(*pBoxX, 0, 10, 1, 1);
    m_Grid.attach(*pBoxY, 1, 10, 1, 1);
    m_Grid.attach(*pBoxZ, 2, 10, 1, 1);
}
