#include <iostream>
#include "ExternalReactionsSubsystem.hpp"

ExternalReactionsSubsystem :: ExternalReactionsSubsystem(){
    m_Name = "External Reactions";
    std :: cout << "In ExternalReactionsSubsystem constuctor" << std :: endl;
}

void ExternalReactionsSubsystem :: Create(){
    std :: cout << "in ExternalReactionsSubsystem::Create" << std :: endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);
    int row = 1;

    m_notebook.set_margin(10);
    m_notebook.set_expand();
    m_Grid.attach(m_notebook, 0, 0);
    m_pages.push_back(std::make_unique<Gtk::Grid>());
    //tabSetup(*m_pages.back());
    m_notebook.append_page(*m_pages.back(), "Force 1");
    
    //Force Name takes in a user input string
    auto nameLabel = Gtk::make_managed<Gtk::Label>("FORCE NAME");
    auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
    nameTextbox->set_text("");
    m_Grid.attach(*nameLabel, 0, row);
    m_Grid.attach(*nameTextbox, 1, row);


    //frame dropdown window
    auto frameLabel = Gtk:: make_managed<Gtk::Label>("FRAME");
    auto frameDropDownList = Gtk::make_managed<Gtk::ComboBoxText>();
    frameDropDownList->append("BODY");
    frameDropDownList->append("LOCAL");
    frameDropDownList->append("WIND");
    m_Grid.attach(*frameLabel, 3,row);
    m_Grid.attach(*frameDropDownList, 4, row);
    
    //Location
    auto locationLabel = Gtk:: make_managed <Gtk::Label> ("LOCATION");
    m_Grid.attach(*locationLabel, 0, row + 2 );

    auto xTextbox = Gtk::make_managed<Gtk::Entry>();
    xTextbox->set_text("X.");

    auto yTextbox = Gtk::make_managed<Gtk::Entry>();
    yTextbox->set_text("Y.");

    auto zTextbox = Gtk::make_managed<Gtk::Entry>();
    zTextbox->set_text("Z.");

    auto LocationUnitDropDown = Gtk::make_managed<Gtk::ComboBoxText>();
    LocationUnitDropDown->append("IN");
    LocationUnitDropDown->append("FT");
    LocationUnitDropDown->append("M");
    LocationUnitDropDown->set_active(0);
    m_Grid.attach(*LocationUnitDropDown, 5, row + 2 );

    m_Grid.attach(*xTextbox, 1, row + 2);
    m_Grid.attach(*yTextbox, 3, row + 2);
    m_Grid.attach(*zTextbox, 4, row + 2);


    //direction
    auto directionLabel = Gtk:: make_managed <Gtk::Label> ("DIRECTION");
    m_Grid.attach(*directionLabel, 0, row + 4 );
}


void tabSetup(Gtk::Grid& ex_grid)
{
    //m_metricList = Gtk::StringList::create({"in, "})

    auto forceLabel = Gtk::make_managed<Gtk::Label>("Force 1");


}