#include "TankDialog.hpp"
#include <iostream>

TankDialog::TankDialog() 
{
    set_title("Tank Setup");
    set_default_size(600, 300);

    // Initialize dialog
    dialogTank = new Gtk::Dialog("Tank Setup", *this);
    dialogTank->set_modal(true);

    // Content area for the dialog
    Gtk::Box* content_area = dynamic_cast<Gtk::Box*>(dialogTank->get_content_area());
    if (content_area) 
    {
        content_area->append(grid);
    }

    // Tank Type ComboBox
    typeComboBox.append("OXIDIZER");
    typeComboBox.append("FUEL");
    grid.attach(*Gtk::make_managed<Gtk::Label>("Type:"), 0, 0);
    grid.attach(typeComboBox, 1, 0);

    // Capacity Entry and Unit
    grid.attach(*Gtk::make_managed<Gtk::Label>(" Capacity = "), 0, 1); // Capacity label
    capacityEntry.set_width_chars(8);                              // Set uniform width for entry
    grid.attach(capacityEntry, 1, 1);
    capacityUnitComboBox.append("LBS");
    capacityUnitComboBox.append("KG");
    capacityUnitComboBox.set_size_request(70, -1);                 // Set width for dropdown
    grid.attach(capacityUnitComboBox, 2, 1);                       // Capacity dropdown

    // Contents Entry and Unit
    grid.attach(*Gtk::make_managed<Gtk::Label>("Contents = "), 3, 1); // Contents label
    contentsEntry.set_width_chars(8);                               // Set uniform width for entry
    grid.attach(contentsEntry, 4, 1);
    contentsUnitComboBox.append("LBS");
    contentsUnitComboBox.append("KG");
    contentsUnitComboBox.set_size_request(50, -1);                  // Set width for dropdown
    grid.attach(contentsUnitComboBox, 5, 1);                        // Contents dropdown

    // Location Section Header
    grid.attach(*Gtk::make_managed<Gtk::Label>("Location:"), 0, 3, 1, 1); // Header spans across 6 columns

    // Row for x, y, z inputs, with one dropdown for the z-axis
    // x-axis
    grid.attach(*Gtk::make_managed<Gtk::Label>("x ="), 0, 4); // x label
    grid.attach(xEntry, 1, 4);                               // x entry

    // y-axis
    grid.attach(*Gtk::make_managed<Gtk::Label>("y ="), 2, 4); // y label
    grid.attach(yEntry, 3, 4);                               // y entry

    // z-axis
    grid.attach(*Gtk::make_managed<Gtk::Label>("z ="), 4, 4); // z label
    grid.attach(zEntry, 5, 4);                               // z entry
    
    //Gtk::ComboBoxText* zUnitComboBox = Gtk::make_managed<Gtk::ComboBoxText>();
    zUnitComboBox = Gtk::make_managed<Gtk::ComboBoxText>();
    zUnitComboBox->append("IN");
    zUnitComboBox->append("FT");
    zUnitComboBox->append("M");
       
    //zUnitComboBox.set_size_request(70, -1); 
    zUnitComboBox->set_active(0);   
    grid.attach(*zUnitComboBox, 6, 4);                       // Dropdown for z



    // Buttons Section
    Gtk::Box* buttonBox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10); // Horizontal box with spacing

    // OK Button
    createButton.set_label("OK");
    createButton.set_hexpand(true); // Allow horizontal expansion
    createButton.set_halign(Gtk::Align::CENTER); // Align horizontally
    createButton.set_margin(10); // Add margin for better appearance
    createButton.set_size_request(400, -1); // Set width to 150 pixels, height unchanged

    // Cancel Button
    cancelButton.set_label("Cancel");
    cancelButton.set_hexpand(true); // Allow horizontal expansion
    cancelButton.set_halign(Gtk::Align::CENTER); // Align horizontally
    cancelButton.set_margin(10); // Add margin for better appearance
    cancelButton.set_size_request(400, -1); // Set width to 150 pixels, height unchanged

    // Pack buttons into the button box
    buttonBox->append(createButton);
    buttonBox->append(cancelButton);

    // Attach button box to the grid
    grid.attach(*buttonBox, 0, 5, 7, 1); // Center buttons and span all columns

    // Call defaultValueFill to set default values for all fields
    defaultValueFill();

    // Show the dialog and all children
    dialogTank->show(); 
}

/*TankDialog::~TankDialog() 
{
    delete zUnitComboBox;  // Proper cleanup
}*/

bool TankDialog::isValidSelection() 
{
    return !typeComboBox.get_active_text().empty() &&
           !capacityEntry.get_text().empty() &&
           !contentsEntry.get_text().empty();
}

void TankDialog::onCreateButtonClicked() 
{
    if (isValidSelection()) 
    {
        //std::cout << "Tank configuration saved!" << std::endl;
        dialogTank->close();
    } 
    else 
    {
        std::cerr << "Please fill out all fields!" << std::endl;
    }
}

void TankDialog::onCancelButtonClicked() 
{
    dialogTank->close();
}

void TankDialog::defaultValueFill() 
{
    // Set default values for the TankDialog fields
    typeComboBox.set_active(1); // Default to "OXIDIZER"
    capacityEntry.set_text("0");
    capacityUnitComboBox.set_active(0); // Default to "LBS"
    contentsEntry.set_text("0");
    contentsUnitComboBox.set_active(0); // Default to "LBS"

    xEntry.set_text("0");
    yEntry.set_text("0");
    zEntry.set_text("0");

    // Assuming there's a zUnitComboBox, set its default value
    //Gtk::ComboBoxText* zUnitComboBox = Gtk::make_managed<Gtk::ComboBoxText>();
    zUnitComboBox->set_active(0); // Default to "IN"
}

