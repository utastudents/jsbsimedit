#include "GainComponentWindow.hpp"

namespace DragDrop
{

GainComponentWindow::GainComponentWindow(std::shared_ptr<IComponentCommon> comp, 
    std::shared_ptr<std::set<std::string>> setOfNames)
        : ComponentWindowCommon(comp, setOfNames)
{
    CreateCommonTab();
    AeroSurface();
    Scheduled();
}

void GainComponentWindow::AeroSurface()
{
    // Creates a Grid to store Label and input:
    Gtk::Grid g;        
    g.set_vexpand(true);
    g.set_hexpand(true);
    g.set_margin_top(75);
    g.set_margin_start(50);

   // AeroSurface has 2 label and 2 entry
    Gtk::Label MAX{"MAX: "};
    Gtk::Label MIN{"MIN: "};

    // Set spacing between max and min by only making space for max label
    MAX.set_margin_bottom(15); 

    g.attach(MAX,1,1);
    g.attach(MIN,1,2);

    Gtk::Entry e_max{};
    Gtk::Entry e_min{};

    // Set spacing for max and min by only making space for max entry
    e_max.set_margin_bottom(15);

    g.attach(e_max,2,1);
    g.attach(e_min,2,2);

    m_noteBook.append_page(g, "AeroSurface");
}

void GainComponentWindow::Scheduled()
{
    // This box is used to Scroll and contain the grid
    Gtk::Box ContainAll;
    ContainAll.set_vexpand(true);
    ContainAll.set_hexpand(true);

    Gtk::Grid g;        
    g.set_vexpand(true);
    g.set_hexpand(true);
    g.set_margin_top(15);
    g.set_margin_start(20);

    // The scroll need a box and any other container(eg. another box, grid, etc...)
    // Box(parent) => Scroll => Grid
    Gtk::ScrolledWindow scrolled;
    scrolled.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    scrolled.set_child(g); // Grid
    ContainAll.append(scrolled); // Box

    // These are the Label and entry
    Gtk::Label Column1{"#"};

    Gtk::Label Label_ind{"Independent Var"};
    Label_ind.set_margin_start(20);

    Gtk::Label Label_val{"Value"};
    Label_val.set_margin_start(30);

    g.attach(Column1,0,0);
    g.attach(Label_ind,1,0);
    g.attach(Label_val,2,0);

    // This creates 99 entry... QUESTION: If user input on row 6 how do we handle user Input?
    int row;
    for(row = 1; row < 100; row++)
    {
        // Only creates Number values
        Gtk::Label rowNum {std::to_string(row)};
        g.attach(rowNum,0,row);

        Gtk::Entry entry_ind{};
        Gtk::Entry entry_var{};

        // All 99 entries
        /*
            LOGIC HERE TO HANDLE ALL USER INPUT & SAVE THEM
        */
        g.attach(entry_ind, 1, row);
        g.attach(entry_var, 2, row);
    }

    m_noteBook.append_page(ContainAll, "Scheduled");
}

void GainComponentWindow::SaveInfo()
{
}

};