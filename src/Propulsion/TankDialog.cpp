#include "TankDialog.hpp"
#include <gtkmm.h>
#include <iostream>
#include <string>
#include <map>
#include "Tank.hpp"

// Constructor
TankDialog::TankDialog() {
    // Set the title and default size for the parent window
    set_title("Tank Setup");
    set_default_size(800, 400);

    dialogTank = new Gtk::Dialog("Tank Setup", *this);
    dialogTank->set_modal(true);

    Gtk::Box* content_area = dynamic_cast<Gtk::Box*>(dialogTank->get_content_area());
    if (content_area) {
        // Add the grid to the content area using pack_start
        content_area->append(grid);
    } else {
        std::cerr << "Error: Content area is not a Gtk::Box!" << std::endl;
    }

    // Add ComboBox for selecting tank type
    typeComboBox.append("OXIDIZER");
    typeComboBox.append("FUEL");

    grid.attach(*Gtk::make_managed<Gtk::Label>("Type:"), 0, 0);
    grid.attach(typeComboBox, 1, 0);

    // Add input field for tank capacity
    grid.attach(*Gtk::make_managed<Gtk::Label>("Capacity:"), 0, 1);
    grid.attach(capacityEntry, 1, 1);

    // Add ComboBox for selecting UNIT
    unitComboBox.append("KG");
    unitComboBox.append("LPG");
    grid.attach(*Gtk::make_managed<Gtk::Label>("Unit:"), 0, 2);
    grid.attach(unitComboBox, 1, 2);

    // For contents:
    grid.attach(*Gtk::make_managed<Gtk::Label>("Contents:"), 0, 3);
    grid.attach(unitComboBox, 1, 3);

    // Location Section (X, Y, Z)
    Gtk::Label* location_header = new Gtk::Label("Location");
    grid.attach(*location_header, 0, 4, 2, 1);

    Gtk::Label* x_label = new Gtk::Label("x =");
    x_entry = new Gtk::Entry();
    Gtk::Label* y_label = new Gtk::Label("y =");
    y_entry = new Gtk::Entry();
    Gtk::Label* z_label = new Gtk::Label("z =");
    z_entry = new Gtk::Entry();

    grid.attach(*x_label, 0, 5, 1, 1);
    grid.attach(*x_entry, 1, 5, 1, 1);
    grid.attach(*y_label, 0, 6, 1, 1);
    grid.attach(*y_entry, 1, 6, 1, 1);
    grid.attach(*z_label, 0, 7, 1, 1);
    grid.attach(*z_entry, 1, 7, 1, 1);

    // Dropdown for Location Unit (IN/FT/M)
    location_dropdown = new Gtk::ComboBoxText();
    location_dropdown->append("IN");
    location_dropdown->append("FT");
    location_dropdown->append("M");
    grid.attach(*location_dropdown, 1, 8, 1, 1);

    // Add OK and Cancel buttons to the bottom of the dialog (after location)
    createButton.set_label(" OK ");
    createButton.set_sensitive(true); // Enable until valid selection is made
    createButton.signal_clicked().connect(sigc::mem_fun(*this, &TankDialog::onCreateButtonClicked));

    cancelButton.set_label("Cancel");
    cancelButton.set_sensitive(true); // Enable until valid selection is made
    cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &TankDialog::onCancelButtonClicked));

    // Now place the buttons in a lower row, below all other content
    grid.attach(createButton, 0, 9);
    grid.attach(cancelButton, 1, 9);

    // Enable button only if the selection is valid
    typeComboBox.signal_changed().connect([this]() {
        cancelButton.set_sensitive(isValidSelection());
    });

    typeComboBox.signal_changed().connect([this]() {
        createButton.set_sensitive(isValidSelection());
    });

    dialogTank->show();
}

// Validate the tank dialog fields
bool TankDialog::isValidSelection() {
    return !typeComboBox.get_active_text().empty() && !capacityEntry.get_text().empty();
}

// Handle Create button click
void TankDialog::onCreateButtonClicked() {
    if (!isValidSelection()) {
        return;
    }

    std::cout << "Tank configuration saved successfully!" << std::endl;
    close(); // Close the dialog
}

// Handle Cancel button click
void TankDialog::onCancelButtonClicked() {
    close(); // Close the dialog
}
