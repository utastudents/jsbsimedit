#pragma once
#ifndef PROPULSIONSUBSYSTEM_HPP
#define PROPULSIONSUBSYSTEM_HPP

#include "inc/Subsystem.hpp"
#include "gtkmm.h"  
#include "PropulsionManager.hpp"
#include "inc/XML_api.hpp"

// Inherit from both Subsystem and Gtk::Window
class PropulsionSubsystem : public Subsystem, public Gtk::Window {
public:
    PropulsionSubsystem();  // Constructor to initialize the window and UI components
    void Create();          // Method to create and display the UI elements
    void on_button_clicked();  // Callback for button click events
    bool checkSelect(const std::string& inp); 
    std::string GetCurrentPlatformDebug();
    std::string EngineOrThruster(const std::string& pulledInput);


    std::string selectedEngine;
    std::string selectedThruster;
    std::string selectedTank;

    


    PropulsionManager m_PropManager;  // Propulsion manager instance
};


#endif // PROPULSIONSUBSYSTEM_HPP