#pragma once

#include "inc/Subsystem.hpp"
#include "inc/XML_api.hpp"

#include "XML/XMLDoc.hpp"
#include <gtkmm.h>

class MainWindow {
	public:
    	MainWindow(Gtk::Grid& m_Grid);
	protected:
    	void textboxesAndLists(Gtk::Grid& m_Grid);
    	void onCheckBoxToggle();
    	void onButtonClicked(Gtk::Grid& m_Grid);
    	void onChooseButtonClicked(); // Adding this declaration
	private:
		//File Handling fields
		JSBEdit::XMLDoc xmlFile;
		Gtk::Label nameEntry;
		

    	Gtk::Box totalArea;
    	Gtk::Box propertyDisplayArea;
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

		
};

