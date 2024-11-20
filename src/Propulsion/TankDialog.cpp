#include <gtkmm.h>
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

