#pragma once

#include "inc/Subsystem.hpp"
#include "inc/XML_api.hpp"

#include "XML/XMLDoc.hpp"
#include <gtkmm.h>

#include <vector>
#include <string>

class MainWindow {
	public:
    	MainWindow(Gtk::Grid& m_Grid);
	protected:
    	void textboxesAndLists(Gtk::Grid& m_Grid);
    	void onCheckBoxToggle();
    	void onButtonClicked(Gtk::Grid& m_Grid);
    	void onChooseButtonClicked(); // Adding this declaration
		void IOSave(std::vector<JSBEdit::XMLNode> children, std::vector<Gtk::CheckButton*> checkboxes, const std::vector<std::string> checkboxLabels);
		void on_checkbox_toggled(const std::string& label, Gtk::CheckButton* checkbox); //std::set<std::string>& toggledCheckboxes); 
		void addPropertiesTextBox(Gtk::Grid& grid, const std::vector<std::string>& properties);


		// void setCheckboxState(const std::string& label, bool state, const std::vector<std::string>& checkboxLabels, const std::vector<Gtk::CheckButton*>& checkboxes);
		//void setCheckboxState(int ID, bool state, const std::vector<Gtk::CheckButton*>& checkboxes);
	private:
		//XML File Handling fields
		JSBEdit::XMLDoc xmlFile;
		
		//Name, Type, Rate
		Gtk::Label name;
		Gtk::Label type;
		Gtk::Label rate;
		Gtk::Entry nameTextBox; // we will validate the input and display error message for invalid input
		Gtk::ComboBoxText typeDropDownList;
    	Gtk::Entry rateTextBox;
    	
		//CheckBoxes
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

		// Set to store unique checkbox labels that have been toggled
 		std::set<std::string> toggledCheckboxes;
		// std::vector<std::string> toggledCheckboxes;
    	

		//Output Area
    	Gtk::Box totalArea;
    	Gtk::Box propertyDisplayArea;
		Gtk::Label propertyName;
		std::vector<std::string> properties;

    	
		//Buttons
		// Gtk::ToggleButton chooseButton;
    	// Gtk::ToggleButton addButton; // we will display an error message if the user tries to add a configuration without
    	// // selecting at least one data type
    	// Gtk::ToggleButton 	deleteButton;
		// Glib::ustring 		chooseLabel;
		// Glib::ustring  		addLabel;
		// Glib::ustring  		deleteLabel;
    	
		//Entry for custom property
    	Gtk::Entry customProperty;
    	

		
};

