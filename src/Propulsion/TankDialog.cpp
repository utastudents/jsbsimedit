#include "TankDialog.hpp"

#include <gtkmm.h>

#include <iostream>

#include <string>

#include <map>

#include "Tank.hpp"


// Constructor

TankDialog::TankDialog() {


   // Set the title and default size for the parent window

   set_title("Tank Setup");

   set_default_size(800, 400);


   dialogTank = new Gtk::Dialog("Tank Setup", *this);

   dialogTank->set_modal(true);


   Gtk::Box* content_area = dynamic_cast<Gtk::Box*>(dialogTank->get_content_area());

   if (content_area) {

       // Add the grid to the content area using pack_start

       content_area->append(grid);

   }

   else {

       std::cerr << "Error: Content area is not a Gtk::Box!" << std::endl;

   }

   // Add ComboBox for selecting tank type

   typeComboBox.append("OXIDIZER");

   typeComboBox.append("FUEL");

   //typeComboBox.set_active_text(m_tank.getFuelType() == 0 ? "FUEL" : "OXIDIZER");

   grid.attach(*Gtk::make_managed<Gtk::Label>("Type:"), 0, 0);

   grid.attach(typeComboBox, 1, 0);





   /// Add input field for tank capacity


   grid.attach(capacityEntry, 1, 1);

    // Add ComboBox for selecting UNIT

   unitComboBox.append("KG");

   unitComboBox.append("LPG");

   //typeComboBox.set_active_text(m_tank.getFuelType() == 0 ? "FUEL" : "OXIDIZER");

   grid.attach(*Gtk::make_managed<Gtk::Label>("  capacity:"), 0, 1);

   grid.attach(unitComboBox, 2, 1);


   ///for contents:


   //capacityEntry.set_text(std::to_string(m_tank.getTankCapacity()));

   grid.attach(capacityEntry, 4, 1);

    // Add ComboBox for selecting UNIT

   unitComboBox.append("KG");

   unitComboBox.append("LPG");

   //typeComboBox.set_active_text(m_tank.getFuelType() == 0 ? "FUEL" : "OXIDIZER");

   grid.attach(*Gtk::make_managed<Gtk::Label>("Contents:"), 3, 1);

   grid.attach(unitComboBox, 5, 1);

    grid.attach(capacityEntry, 6, 1);

    // Add ComboBox for selecting UNIT

   unitComboBox.append("KG");

   unitComboBox.append("LPG");







   // Add Create button

   createButton.set_label(" OK   ");

   createButton.set_sensitive(true); // Disable until valid selection is made

   createButton.signal_clicked().connect(sigc::mem_fun(*this, &TankDialog::onCreateButtonClicked));

   grid.attach(createButton, 0, 3);


   // Add Cancel button

   cancelButton.set_label("Cancel");

   cancelButton.set_sensitive(true); // Disable until valid selection is made

   cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &TankDialog::onCancelButtonClicked));

   grid.attach(cancelButton, 1, 3);


   // Enable button only if the selection is valid

   typeComboBox.signal_changed().connect([this]() {

       cancelButton.set_sensitive(isValidSelection());

   });

typeComboBox.signal_changed().connect([this]() {

       createButton.set_sensitive(isValidSelection());

   });

   dialogTank->show();

}


// Validate the tank dialog fields

bool TankDialog::isValidSelection() {

   return !typeComboBox.get_active_text().empty() && !capacityEntry.get_text().empty();

}


// Show a popup for invalid input

/*void TankDialog::showReselectPopup() {

   Gtk::MessageDialog dialog(*this, "Invalid Input", false, Gtk::MessageType::ERROR, Gtk::ButtonsType::OK);

   dialog.set_secondary_text("Please ensure all fields are filled out correctly.");

   dialog.run();

}*/


// Handle Create button click

void TankDialog::onCreateButtonClicked() {

   if (!isValidSelection()) {

       //showReselectPopup();

       return;

   }

/*

   // Save data to the Tank object

   m_tank.setFuelType(typeComboBox.get_active_text() == "FUEL" ? 0 : 1);

   m_tank.setTankCapacity(std::stod(capacityEntry.get_text()));

*/

   std::cout << "Tank configuration saved successfully!" << std::endl;

   close(); // Close the dialog

}

void TankDialog::onCancelButtonClicked() {

   if (!isValidSelection()) {

       //showReselectPopup();

       return;

   }



   close(); // Close the dialog

}