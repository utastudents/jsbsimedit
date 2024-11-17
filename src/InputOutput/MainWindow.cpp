#include "MainWindow.hpp"

// constructor - manage main window
MainWindow::MainWindow(Gtk::Grid& m_Grid) {
    textboxesAndLists(m_Grid);
}

// create and manage textboxes and drop down lists
void MainWindow::textboxesAndLists(Gtk::Grid& m_Grid) {
    // creates name label and text box, then attaches them to the grid
    auto nameLabel = Gtk::make_managed<Gtk::Label>("Name(*)");
    auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
    m_Grid.attach(*nameLabel, 0, 0);
    m_Grid.attach(*nameTextbox, 1, 0);
    
    // creates type label and drop down list, then attaches them to the grid
    auto typeLabel = Gtk::make_managed<Gtk::Label>("Type(*)");
    auto typeDropDownList = Gtk::make_managed<Gtk::ComboBoxText>();
    // adds "CSV" and "Tabular" options to the drop down list
    typeDropDownList->append("CSV");
    typeDropDownList->append("Tabular");
    // defaults to "CSV" for the drop down list
    typeDropDownList->set_active(0);
    m_Grid.attach(*typeLabel, 0, 1);
    m_Grid.attach(*typeDropDownList, 1, 1);
    
    // creates rate label and text box, then attaches them to the grid
    auto rateLabel = Gtk::make_managed<Gtk::Label>("Rate(*)");
    auto rateTextbox = Gtk::make_managed<Gtk::Entry>();
    m_Grid.attach(*rateLabel, 0, 2);
    m_Grid.attach(*rateTextbox, 1, 2);
    
}

// create and manage checkboxes
void MainWindow::onCheckBoxToggle() {}

// create and manage buttons
void MainWindow::onButtonClicked() {}
