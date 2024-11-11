#pragma once

#include "MainWindow.hpp"

class PopUpWindow : public MainWindow {
    public:
        PopUpWindow(); // Constructor, initializes pop-up window components.
        ~PopUpWindow(); // Destructor, cleans up resources when window closes

    protected:
        void onButtonClicked(); // handler for button click actions

    private:
        Gtk::Label currentPropertyValue; // Displays currently selected property
        Gtk::Button filterButton; // Button to filter the list of properties
        Gtk::Entry filterTextBox; // Input field for filtering properties
        Gtk::Button showAllButton; // Button to reset and show all properties
        Gtk::Button okButton; // OK button, confirms selection and closes pop-up
        Gtk::Button cancelButton; // Cancel button, discards changes and closes pop-up
        Gtk::Button closeButton; // Close button, closes the pop-up window
        int visibleProperties; // Count of visible properties after filtering
        int hiddenProperties; // Count of hidden properties after filtering
        Gtk::ScrolledWindow scrolledWindowV; // Vertical scrolling window for property list
        Gtk::ScrolledWindow scrolledWindowH; // Horizontal scrolling window for property list
};
