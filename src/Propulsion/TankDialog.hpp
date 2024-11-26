/*#ifndef TANK_DIALOG_HPP
#define TANK_DIALOG_HPP
#include <map>
#include <string>
#include <iostream>
#include <gtk/gtk.h>
#include <gtkmm.h>


class TankDialog {
public:
    // Constructor
    TankDialog();
    void show(); // Show the dialog
    
protected:
    // Signal handlers
    void onConfirm();
    void onCancel();
    void defaultValueFill();
    void onResponse(int response_id);  // Declare onResponse method
private:
    // Widgets
    Gtk::Dialog* dialogTK;
    Gtk::Grid grid;

    // TODO: Add Widgets for tank dialog box

};

#endif // TANK_DIALOG_HPP*/

#pragma once
#ifndef TANK_DIALOG_H
#define TANK_DIALOG_H

#include <map>
#include <string>
#include <iostream>
#include <gtk/gtk.h>
#include <gtkmm.h>

#include "Tank.hpp"


class TankDialog : public Gtk::Window {
public:
    TankDialog();

    bool run_dialog(); 
    void show();

private:
    Gtk::Dialog* dialogTank;

    Gtk::Grid grid;
    Gtk::ComboBoxText typeComboBox;
    Gtk::Entry capacityEntry;
    Gtk::Button cancelButton;
    Gtk::Button createButton;

    Gtk::ComboBoxText unitComboBox;
    bool isValidSelection(); // Validate user input
    void onCreateButtonClicked(); // Handle Create button click
    void onCancelButtonClicked(); 
};

#endif // TANKDIALOG_HPP