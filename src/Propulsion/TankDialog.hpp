#pragma once
#ifndef TANK_DIALOG_H
#define TANK_DIALOG_H

#include <gtkmm.h>

class TankDialog : public Gtk::Window {
public:
    TankDialog(); // Constructor
    virtual ~TankDialog() = default;
     // Helper methods
    bool isValidSelection();
    void onCreateButtonClicked();
    void onCancelButtonClicked();

    // set default values method 
    void defaultValueFill();

    // Main dialog and layout
    Gtk::Dialog* dialogTank;
    Gtk::Grid grid;

    // Input widgets
    Gtk::ComboBoxText typeComboBox;
    Gtk::Entry capacityEntry;
    Gtk::ComboBoxText capacityUnitComboBox;
    Gtk::Entry contentsEntry;
    Gtk::ComboBoxText contentsUnitComboBox;

    Gtk::Entry xEntry, yEntry, zEntry;
    Gtk::ComboBoxText* zUnitComboBox; 
    Gtk::ComboBoxText locationUnitComboBox;

    // Buttons
    Gtk::Button createButton;
    Gtk::Button cancelButton;
};

#endif 
