#include "MainWindow.hpp"
#include "IOSubSystem.hpp"

// constructor - create and manage main window
MainWindow::MainWindow() {
    // creates name label and text box, then attaches them to the grid
    auto nameLabel = Gtk::make_managed<Gtk::Label>("Name(*)");
    auto nameTextbox = Gtk::make_managed<Gtk::Entry>();
    m_Grid.attach(*nameLabel, 0, 0);
    m_Grid.attach(*nameTextbox, 1, 0);
}

// create and manage checkboxes
void MainWindow::onCheckBoxToggle() {}

// create and manage buttons
void MainWindow::onButtonClicked() {}
