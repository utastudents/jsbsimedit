#ifndef ENGINE_THRUSTER_DIALOG_HPP
#define ENGINE_THRUSTER_DIALOG_HPP
#include <map>
#include <string>
#include <iostream>
#include <gtk/gtk.h>
#include <gtkmm.h>
#include "PropulsionSubsystem.hpp"

class PropulsionSubsystem;

class EngineThrusterDialog : public Gtk::Window {
public:
    EngineThrusterDialog(const std::string& engine, const std::string& thruster);
    void show(); // Show the dialog
    // Signal handlers
    void onConfirm();
    void onCancel();
    void defaultValueFill(const std::string& engine, const std::string& thruster);
    void onResponse(int response_id);  // Declare onResponse method

private:
    // Widgets
    Gtk::Dialog* dialogEng;
    Gtk::Grid grid;

    Gtk::Entry* x_entry, * y_entry, * z_entry;
    Gtk::ComboBoxText* location_dropdown;
    Gtk::Entry* roll_entry, * pitch_entry, * yaw_entry;
    Gtk::ComboBoxText* orient_dropdown;

    Gtk::Entry* thruster_name_entry;
    Gtk::Entry* thruster_x_entry, * thruster_y_entry, * thruster_z_entry;
    Gtk::ComboBoxText* thruster_location_dropdown;
    Gtk::Entry* thruster_roll_entry, * thruster_pitch_entry, * thruster_yaw_entry;
    Gtk::ComboBoxText* thruster_orient_dropdown;
};

#endif // ENGINE_THRUSTER_DIALOG_HPP
