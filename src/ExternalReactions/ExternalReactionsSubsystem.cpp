#include <iostream>
#include "ExternalReactionsSubsystem.hpp"

ExternalReactionsSubsystem::ExternalReactionsSubsystem() {
    m_Name = "ExternalReactions";
    std::cout << "In ExternalReactionSubsystem constructor" << std::endl;
}

void ExternalReactionsSubsystem::Create() {
    std::cout << "In ExternalReactionSubsystem::Create" << std::endl;


    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    for(int i=0; i < 10; i++) {
        for (int j=0; j < 10; j++) {
            auto s = Glib::ustring::compose("button (%1 %2)", i, j);
            auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
            m_Grid.attach(*pButton, i, j);
        }
    }
}