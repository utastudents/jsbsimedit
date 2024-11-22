#pragma once
#ifndef PROPULSIONSUBSYSTEM_HPP
#define PROPULSIONSUBSYSTEM_HPP

#include "inc/Subsystem.hpp"
#include "gtkmm.h"  
#include "PropulsionManager.hpp"

// Inherit from both Subsystem and Gtk::Window
class PropulsionSubsystem : public Subsystem, public Gtk::Window {
public:
    void someFunction();

    PropulsionSubsystem() : m_PropManager(*this) {}  // Default constructor
    //explicit PropulsionSubsystem(Gtk::Window& parent) : Gtk::Window(), m_PropManager(parent) {}
    //PropulsionSubsystem(Gtk::Window& parent) : Gtk::Window(), m_PropManager(parent) {}
    explicit PropulsionSubsystem(Gtk::Window& parent); // Declaration
    //PropulsionSubsystem(Gtk::Window& parentWindow);  // Constructor to initialize the window and UI components
    void Create();          // Method to create and display the UI elements
    void on_button_clicked();  // Callback for button click events
    bool checkSelect(const std::string& inp); 
    std::string GetCurrentPlatform();

    std::string selectedEngine;
    std::string selectedThruster;
    std::string selectedTank;

private:
    PropulsionManager m_PropManager;  // Propulsion manager instance
};


#endif // PROPULSIONSUBSYSTEM_HPP