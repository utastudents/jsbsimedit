#include <iostream>
#include "GroundReactionsSubsystem.hpp"

GroundReactionsSubsystem::GroundReactionsSubsystem() {
    m_Name = "GroundReactions";
    std::cout << "In GroundReactionsSubsystem contructor" << std::endl; 
}

GroundReactionsSubsystem::~GroundReactionsSubsystem() {

}

void GroundReactionsSubsystem::Create() {
    std :: cout << "in GroundReactionsSubsystem::Create" << std :: endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 3 ; j++){
            auto s = Glib::ustring::compose("button (%1,%2)",i,j);
            auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
            m_Grid.attach(*pButton,i,j);
        }
    }
}
