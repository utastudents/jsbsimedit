#pragma once

#include "inc/Subsystem.hpp"
#include "gtkmm.h"  // Ensure you have the right include for GTKmm
#include "PropulsionManager.hpp"

// Inherit from both Subsystem and Gtk::Window
class PropulsionSubsystem : public Subsystem, public Gtk::Window {
public:
    PropulsionSubsystem();  // Constructor to initialize the window and UI components
    void Create();          // Method to create and display the UI elements
    void on_button_clicked();  // Callback for button click events

    PropulsionManager m_PropManager;  // Propulsion manager instance
};
