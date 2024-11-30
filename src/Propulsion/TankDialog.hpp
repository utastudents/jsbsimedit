#pragma once
#ifndef TANK_DIALOG_H
#define TANK_DIALOG_H

#include <gtkmm.h>

class TankDialog : public Gtk::Window {
public:
    TankDialog(); // Constructor
    virtual ~TankDialog() = default;

private:
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
    Gtk::ComboBoxText locationUnitComboBox;

    // Buttons
    Gtk::Button createButton;
    Gtk::Button cancelButton;

    // Helper methods
    bool isValidSelection();
    void onCreateButtonClicked();
    void onCancelButtonClicked();
};

#endif // TANK_DIALOG_HPP
