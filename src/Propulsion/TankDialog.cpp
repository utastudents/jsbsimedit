/*#include <gtkmm.h>
#include <iostream>
#include <map>
#include "TankDialog.hpp"


TankDialog::TankDialog() {
    // TODO: Initialize dialog components

    // Set the title and default size for the parent window
    dialogTK->set_title("Tank Setup");
    dialogTK->set_default_size(400, 400);


    // Create the dialog window
    dialogTK = new Gtk::Dialog("Tank Setup");
    dialogTK->set_modal(true);

    // Use GTK_RESPONSE_ACCEPT for OK and GTK_RESPONSE_REJECT for Cancel
    dialogTK->add_button("OK", GTK_RESPONSE_ACCEPT);  // OK button
    dialogTK->add_button("Cancel", GTK_RESPONSE_REJECT);  // Cancel button

    // Create a Gtk::Box to hold the grid (as the content area)
    Gtk::Box* content_area = dynamic_cast<Gtk::Box*>(dialogTK->get_content_area());
    if (content_area) {
        // Add the grid to the content area using pack_start
        content_area->append(grid);  // In GTKmm 4, append() is used instead of pack_start
    }
    else {
        std::cerr << "Error: Content area is not a Gtk::Box!" << std::endl;
    }
    // TODO: Implement widgets for Tank Dialog boxes

    // Show the dialog window
    dialogTK->show();

    // Connect to the response signal 
    // TODO: Check if values are empty or not
    // TODO: Fix buttons so the close dialog if check passes
    dialogTK->signal_response().connect(sigc::mem_fun(*this, &TankDialog::onResponse));
}



// Signal handler for dialog responses
void TankDialog::onResponse(int response_id) {
    if (response_id == GTK_RESPONSE_ACCEPT) {
        onConfirm();
    }
    else {
        onCancel();
    }
}

// Handle Confirm button press
void TankDialog::onConfirm() {
    std::cout << "Confirmed! Settings have been applied." << std::endl;
}

// Handle Cancel button press
void TankDialog::onCancel() {
    std::cout << "Canceled! No changes were applied." << std::endl;
}

void TankDialog::defaultValueFill(){
    // TODO: Implement defaultValueFill logic
    std::cout << "Unable to fill tank dialog box..." << std::endl;
}
*/

#include "TankDialog.hpp"
#include <gtkmm.h>
#include <iostream>
#include <string>
#include <map>
#include "Tank.hpp"


// Constructor
TankDialog::TankDialog(Gtk::Window& parent, Tank& tank)
    : Gtk::Dialog("Tank Setup", parent), tank_(tank) {
    set_default_size(400, 200);

    // Configure grid layout
    grid.set_column_spacing(10);
    grid.set_row_spacing(10);
    get_content_area()->append(grid);

    // Add ComboBox for selecting tank type
    typeComboBox.append("FUEL");
    typeComboBox.append("WATER");
    typeComboBox.set_active_text(tank.getFuelType() == 0 ? "FUEL" : "WATER");
    grid.attach(*Gtk::make_managed<Gtk::Label>("Type:"), 0, 0);
    grid.attach(typeComboBox, 1, 0);

    // Add input field for tank capacity
    grid.attach(*Gtk::make_managed<Gtk::Label>("Capacity (LBS):"), 0, 1);
    capacityEntry.set_text(std::to_string(tank.getTankCapacity()));
    grid.attach(capacityEntry, 1, 1);

    // Add Create button
    createButton.set_label("Create");
    createButton.set_sensitive(false); // Disable until valid selection is made
    createButton.signal_clicked().connect(sigc::mem_fun(*this, &TankDialog::onCreateButtonClicked));
    grid.attach(createButton, 1, 2);

    // Enable button only if the selection is valid
    typeComboBox.signal_changed().connect([this]() {
        createButton.set_sensitive(isValidSelection());
    });
}

// Validate the tank dialog fields
bool TankDialog::isValidSelection() {
    return !typeComboBox.get_active_text().empty() && !capacityEntry.get_text().empty();
}

// Show a popup for invalid input
/*void TankDialog::showReselectPopup() {
    Gtk::MessageDialog dialog(*this, "Invalid Input", false, Gtk::MessageType::ERROR, Gtk::ButtonsType::OK);
    dialog.set_secondary_text("Please ensure all fields are filled out correctly.");
    dialog.run();
}*/

// Handle Create button click
void TankDialog::onCreateButtonClicked() {
    if (!isValidSelection()) {
        showReselectPopup();
        return;
    }

    // Save data to the Tank object
    tank_.setFuelType(typeComboBox.get_active_text() == "FUEL" ? 0 : 1);
    tank_.setTankCapacity(std::stod(capacityEntry.get_text()));

    std::cout << "Tank configuration saved successfully!" << std::endl;
    close(); // Close the dialog
}

void TankDialog::showReselectPopup() {
    Gtk::MessageDialog dialog(*this, "Invalid Selection", false, Gtk::MessageType::ERROR);
    Dialog :set_modal(true); // Make it modal
    Dialog :show();          // Show the dialog
}

// Fix: Provide arguments for Tank object
void PropulsionManager::showTankSetup(Gtk::Window& parentWindow) {
    Tank selectedTank(0, 100.0, 50.0); // Initialize with valid arguments
    TankDialog dialog(parentWindow, selectedTank);

    dialog.present(); // Replace run() with present()
}

class TankDialog : public Gtk::Dialog {
public:
    void run_dialog() {
        show(); // Or any specific functionality for running your dialog
    }
};