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


    m_notebook.set_margin(10);
    m_notebook.set_expand();

    m_Grid.attach(m_notebook, 0, 0);

    m_pages.push_back(std::make_unique<Gtk::Grid>());
    //tabSetup(*m_pages.back());
    m_notebook.append_page(*m_pages.back(), "Force 1");




    for(int i=0; i < 10; i++) {
        for (int j=0; j < 10; j++) {
            auto s = Glib::ustring::compose("button (%1 %2)", i, j);
            auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
            m_Grid.attach(*pButton, i, j);
        }
    }
}

void tabSetup(Gtk::Grid& ex_grid)
{
    //m_metricList = Gtk::StringList::create({"in, "})

    auto forceLabel = Gtk::make_managed<Gtk::Label>("Force 1");


}