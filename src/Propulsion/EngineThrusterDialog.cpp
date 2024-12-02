#include <gtkmm.h>
#include <iostream>
#include <map>
#include "EngineThrusterDialog.hpp"
#include "PropulsionSubsystem.hpp"

EngineThrusterDialog::EngineThrusterDialog() {
    // TODO: If existing pair make sure changes are included in dialog box

    // Set the title and default size for the parent window
    set_title("Engine/Thruster Setup");
    set_default_size(400, 400);

    // Create the dialog window
    dialogEng = new Gtk::Dialog("Engine/Thruster Setup", *this);
    dialogEng->set_modal(true);

    // Use GTK_RESPONSE_ACCEPT for OK and GTK_RESPONSE_REJECT for Cancel
    dialogEng->add_button("OK", GTK_RESPONSE_ACCEPT);  // OK button
    dialogEng->add_button("Cancel", GTK_RESPONSE_REJECT);  // Cancel button

    // Create a Gtk::Box to hold the grid (as the content area)
    Gtk::Box* content_area = dynamic_cast<Gtk::Box*>(dialogEng->get_content_area());
    if (content_area) {
        // Add the grid to the content area using pack_start
        content_area->append(grid);  // In GTKmm 4, append() is used instead of pack_start
    }
    else {
        std::cerr << "Error: Content area is not a Gtk::Box!" << std::endl;
    }

    // Engine Section
    Gtk::Label* engine_header = new Gtk::Label("Engine");
    grid.attach(*engine_header, 0, 0, 2, 1);

    // Engine Name Field
    // TODO: Change name to selected engine name from dropdown 
    Gtk::Label* engine_name_label = new Gtk::Label("Engine Name:");
    engine_name_entry = new Gtk::Entry();
    grid.attach(*engine_name_label, 0, 1, 1, 1);
    grid.attach(*engine_name_entry, 1, 1, 1, 1);

    // Location Subheader
    Gtk::Label* location_header = new Gtk::Label("Location");
    grid.attach(*location_header, 0, 2, 2, 1);

    // X, Y, Z fields for location
    Gtk::Label* x_label = new Gtk::Label("x =");
    x_entry = new Gtk::Entry();
    Gtk::Label* y_label = new Gtk::Label("y =");
    y_entry = new Gtk::Entry();
    Gtk::Label* z_label = new Gtk::Label("z =");
    z_entry = new Gtk::Entry();

    grid.attach(*x_label, 0, 3, 1, 1);
    grid.attach(*x_entry, 1, 3, 1, 1);
    grid.attach(*y_label, 0, 4, 1, 1);
    grid.attach(*y_entry, 1, 4, 1, 1);
    grid.attach(*z_label, 0, 5, 1, 1);
    grid.attach(*z_entry, 1, 5, 1, 1);

    // Dropdown for Location Unit (IN/FT/M)
    location_dropdown = new Gtk::ComboBoxText();
    location_dropdown->append("IN");
    location_dropdown->append("FT");
    location_dropdown->append("M");
    grid.attach(*location_dropdown, 1, 6, 1, 1);

    // Orientation Subheader
    Gtk::Label* orient_header = new Gtk::Label("Orient");
    grid.attach(*orient_header, 0, 7, 2, 1);

    // Roll, Pitch, Yaw fields
    Gtk::Label* roll_label = new Gtk::Label("roll =");
    roll_entry = new Gtk::Entry();
    Gtk::Label* pitch_label = new Gtk::Label("pitch =");
    pitch_entry = new Gtk::Entry();
    Gtk::Label* yaw_label = new Gtk::Label("yaw =");
    yaw_entry = new Gtk::Entry();

    grid.attach(*roll_label, 0, 8, 1, 1);
    grid.attach(*roll_entry, 1, 8, 1, 1);
    grid.attach(*pitch_label, 0, 9, 1, 1);
    grid.attach(*pitch_entry, 1, 9, 1, 1);
    grid.attach(*yaw_label, 0, 10, 1, 1);
    grid.attach(*yaw_entry, 1, 10, 1, 1);

    // Dropdown for Orientation Unit (DEG/RAD)
    orient_dropdown = new Gtk::ComboBoxText();
    orient_dropdown->append("DEG");
    orient_dropdown->append("RAD");
    grid.attach(*orient_dropdown, 1, 11, 1, 1);

    // Feed Section
    Gtk::Label* feed_header = new Gtk::Label("Feed");
    grid.attach(*feed_header, 0, 12, 2, 1);

    // Feed Display (empty for now)
    Gtk::Entry* feed_display = new Gtk::Entry();
    grid.attach(*feed_display, 1, 13, 1, 1);

    // Thruster Section
    // TODO: Change name to selected thruster name from dropdown 
    Gtk::Label* thruster_header = new Gtk::Label("Thruster");
    grid.attach(*thruster_header, 0, 14, 2, 1);

    // Thruster Name Field
    Gtk::Label* thruster_name_label = new Gtk::Label("Thruster Name:");
    thruster_name_entry = new Gtk::Entry();
    grid.attach(*thruster_name_label, 0, 15, 1, 1);
    grid.attach(*thruster_name_entry, 1, 15, 1, 1);

    // Thruster Location Subheader
    Gtk::Label* thruster_location_header = new Gtk::Label("Location");
    grid.attach(*thruster_location_header, 0, 16, 2, 1);

    // X, Y, Z fields for Thruster Location
    Gtk::Label* thruster_x_label = new Gtk::Label("x =");
    thruster_x_entry = new Gtk::Entry();
    Gtk::Label* thruster_y_label = new Gtk::Label("y =");
    thruster_y_entry = new Gtk::Entry();
    Gtk::Label* thruster_z_label = new Gtk::Label("z =");
    thruster_z_entry = new Gtk::Entry();

    grid.attach(*thruster_x_label, 0, 17, 1, 1);
    grid.attach(*thruster_x_entry, 1, 17, 1, 1);
    grid.attach(*thruster_y_label, 0, 18, 1, 1);
    grid.attach(*thruster_y_entry, 1, 18, 1, 1);
    grid.attach(*thruster_z_label, 0, 19, 1, 1);
    grid.attach(*thruster_z_entry, 1, 19, 1, 1);

    // Dropdown for Thruster Location Unit
    thruster_location_dropdown = new Gtk::ComboBoxText();
    thruster_location_dropdown->append("IN");
    thruster_location_dropdown->append("FT");
    thruster_location_dropdown->append("M");
    grid.attach(*thruster_location_dropdown, 1, 20, 1, 1);

    // Thruster Orientation Subheader
    Gtk::Label* thruster_orient_header = new Gtk::Label("Orient");
    grid.attach(*thruster_orient_header, 0, 21, 2, 1);

    // Roll, Pitch, Yaw fields for Thruster Orientation
    Gtk::Label* thruster_roll_label = new Gtk::Label("roll =");
    thruster_roll_entry = new Gtk::Entry();
    Gtk::Label* thruster_pitch_label = new Gtk::Label("pitch =");
    thruster_pitch_entry = new Gtk::Entry();
    Gtk::Label* thruster_yaw_label = new Gtk::Label("yaw =");
    thruster_yaw_entry = new Gtk::Entry();

    grid.attach(*thruster_roll_label, 0, 22, 1, 1);
    grid.attach(*thruster_roll_entry, 1, 22, 1, 1);
    grid.attach(*thruster_pitch_label, 0, 23, 1, 1);
    grid.attach(*thruster_pitch_entry, 1, 23, 1, 1);
    grid.attach(*thruster_yaw_label, 0, 24, 1, 1);
    grid.attach(*thruster_yaw_entry, 1, 24, 1, 1);

    // Dropdown for Thruster Orientation Unit (DEG/RAD)
    thruster_orient_dropdown = new Gtk::ComboBoxText();
    thruster_orient_dropdown->append("DEG");
    thruster_orient_dropdown->append("RAD");
    grid.attach(*thruster_orient_dropdown, 1, 25, 1, 1);

    // Fill default values before showing the dialog
    defaultValueFill();

    // Show the dialog window
    dialogEng->show();

    // Connect to the response signal
    // TODO: Check if values are empty or not
    // TODO: Fix buttons so the close dialog if check passes
    dialogEng->signal_response().connect(sigc::mem_fun(*this, &EngineThrusterDialog::onResponse));
}



// Signal handler for dialog responses
void EngineThrusterDialog::onResponse(int response_id) {
    if (response_id == GTK_RESPONSE_ACCEPT) {
        onConfirm();
    }
    else {
        onCancel();
    }
}

// Handle Confirm button press
void EngineThrusterDialog::onConfirm() {
    std::cout << "Confirmed! Settings have been applied." << std::endl;
}

// Handle Cancel button press
void EngineThrusterDialog::onCancel() {
    std::cout << "Canceled! No changes were applied." << std::endl;
}

void EngineThrusterDialog::defaultValueFill() {
    // Set default values for other fields (e.g., location, orientation, etc.)
    PropulsionSubsystem propSubsystem;
    engine_name_entry->set_text(propSubsystem.getSelectedEngine());
    x_entry->set_text("0.0");
    y_entry->set_text("0.0");
    z_entry->set_text("0.0");
    roll_entry->set_text("0.0");
    pitch_entry->set_text("0.0");
    yaw_entry->set_text("0.0");
    location_dropdown->set_active(0);  // Default to "IN"
    orient_dropdown->set_active(0);  // Default to "DEG"
    thruster_name_entry->set_text(propSubsystem.getSelectedThruster());
    thruster_x_entry->set_text("0.0");
    thruster_y_entry->set_text("0.0");
    thruster_z_entry->set_text("0.0");
    thruster_roll_entry->set_text("0.0");
    thruster_pitch_entry->set_text("0.0");
    thruster_yaw_entry->set_text("0.0");
    thruster_location_dropdown->set_active(0);  // Default to "IN"
    thruster_orient_dropdown->set_active(0);  // Default to "DEG"
}

//This function accepts a preset string and updates the dialog fields based on predefined values for that preset.
void EngineThrusterDialog::presetValueFill(const std::string& preset) {
    if (preset == "Preset1") {
        // Apply values for Preset1
        engine_name_entry->set_text("Engine A");
        x_entry->set_text("10.0");
        y_entry->set_text("15.0");
        z_entry->set_text("5.0");
        roll_entry->set_text("5.0");
        pitch_entry->set_text("10.0");
        yaw_entry->set_text("0.0");
        location_dropdown->set_active(1);  // Default to "FT"
        orient_dropdown->set_active(1);  // Default to "RAD"

        thruster_name_entry->set_text("Thruster X");
        thruster_x_entry->set_text("8.0");
        thruster_y_entry->set_text("6.0");
        thruster_z_entry->set_text("2.0");
        thruster_roll_entry->set_text("2.0");
        thruster_pitch_entry->set_text("4.0");
        thruster_yaw_entry->set_text("1.0");
        thruster_location_dropdown->set_active(1);  // Default to "FT"
        thruster_orient_dropdown->set_active(1);  // Default to "RAD"
    }
    else if (preset == "Preset2") {
        // Apply values for Preset2
        engine_name_entry->set_text("Engine B");
        x_entry->set_text("20.0");
        y_entry->set_text("25.0");
        z_entry->set_text("15.0");
        roll_entry->set_text("15.0");
        pitch_entry->set_text("20.0");
        yaw_entry->set_text("5.0");
        location_dropdown->set_active(2);  // Default to "M"
        orient_dropdown->set_active(0);  // Default to "DEG"

        thruster_name_entry->set_text("Thruster Y");
        thruster_x_entry->set_text("12.0");
        thruster_y_entry->set_text("10.0");
        thruster_z_entry->set_text("8.0");
        thruster_roll_entry->set_text("3.0");
        thruster_pitch_entry->set_text("6.0");
        thruster_yaw_entry->set_text("2.0");
        thruster_location_dropdown->set_active(2);  // Default to "M"
        thruster_orient_dropdown->set_active(0);  // Default to "DEG"
    }
    else {
        std::cerr << "Unknown preset: " << preset << std::endl;
    }
}
