#pragma once
#include "inc/Subsystem.hpp"
// #include "MainWindow.hpp"
#include <gtkmm.h>

class IOSubSystem : public Subsystem
{
  public:
    IOSubSystem();
    void Create();
  /*
  private:
    Gtk::Button chooseButton;
    Gtk::Button addButton; // we will display an error message if the user tries to add a configuration without
    // selecting at least one data type
    Gtk::Button deleteButton;
    Gtk::CheckButton checkboxSimulation;
    Gtk::CheckButton checkboxAtmosphere;
    Gtk::CheckButton checkboxMassprops;
    Gtk::CheckButton checkboxAerosurfaces;
    Gtk::CheckButton checkboxRates;
    Gtk::CheckButton checkboxVelocities;
    Gtk::CheckButton checkboxForces;
    Gtk::CheckButton checkboxMoments;
    Gtk::CheckButton checkboxPosition;
    Gtk::CheckButton checkboxCoefficients;
    Gtk::CheckButton checkboxGroundReactions;
    Gtk::CheckButton checkboxFCS;
    Gtk::CheckButton checkboxPropulsion;
    Gtk::Entry nameTextBox; // we will validate the input and display error message for invalid input
    Gtk::ComboBoxText typeDropDownList;
    Gtk::Entry rateTextBox;
    Gtk::Entry customProperty;
    Gtk::Label nameEntry;
    Gtk::Label typeEntry;
    Gtk::Label rateEntry;
  */
};