#ifndef TANK_DIALOG_HPP
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

#endif // TANK_DIALOG_HPP