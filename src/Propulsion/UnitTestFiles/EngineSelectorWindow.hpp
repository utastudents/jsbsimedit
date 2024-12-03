#pragma once

#include <gtkmm.h>  // Include GTKmm for the necessary widgets

class EngineSelectorWindow : public Gtk::Window {  // Inheriting from Gtk::Window
public:
    EngineSelectorWindow();  // Constructor declaration
    virtual ~EngineSelectorWindow() {}

protected:
    // Members
    Gtk::Grid m_Grid;              // Layout container
    Gtk::Label m_Label;            // Label for "Select Engine:"
    Gtk::ComboBoxText m_ComboBox;  // ComboBox for engine selection
    Gtk::Button m_Button;          // Button for closing the window

    // Signal handlers
    void on_button_clicked();  // Close window when the button is clicked
};
