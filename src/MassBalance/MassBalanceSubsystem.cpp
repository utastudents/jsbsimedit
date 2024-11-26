#include <iostream>
#include "MassBalanceSubsystem.hpp"
#include "Location.hpp" 
#include <vector>


MassBalanceSubsystem::MassBalanceSubsystem() {
    m_Name = "Mass Balance";
    std::cout << "In MassBalanceSubsystem constructor" << std::endl; 
}

void MassBalanceSubsystem::Create() {
    std::cout << "In MassBalanceSubsystem::Create" << std::endl;

    //test values for location object
    m_Location.setLocation(1.0f, 2.0f, 3.0f);
    m_Location.setUnits("in");
    

    //test values for empty mass
    m_Emptymass.setEmptyMass(50.0f);
    m_Emptymass.setUnits("lbs");
    
    //test values for moment of inertia
    m_fuselage.setMass(1000.0);
    m_fuselage.setLength(30.0);
    m_fuselage.setRadius(5.0);

    m_leftWing.setMass(500.0);
    m_leftWing.setSpan(20.0);
    m_leftWing.setChord(5.0);

    m_rightWing.setMass(500.0);
    m_rightWing.setSpan(20.0);
    m_rightWing.setChord(5.0);

    m_tail.setMass(200.0);
    m_tail.setSpan(10.0);
    m_tail.setChord(4.0); 

    MassBalance::Airplane m_airplane(m_fuselage, m_leftWing, m_rightWing, m_tail);

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);
    m_Grid.set_margin(10);
    

    // empty weight label
    auto label_empty_weight = Gtk::make_managed<Gtk::Label>("Empty Weight(*)");
    m_Grid.attach(*label_empty_weight, 0, 0);
    
    // box to view weight
    auto entry_empty_weight = Gtk::make_managed<Gtk::Entry>();
    entry_empty_weight->set_editable(false);
    m_Grid.attach(*entry_empty_weight, 1, 0);
    entry_empty_weight->set_text(std::to_string(m_Emptymass.getEmptyMass()));

    // dropdown to choose lbs or kg for empty mass
    auto combo_units = Gtk::make_managed<Gtk::ComboBoxText>();
    combo_units->append("lbs");
    combo_units->append("kgs");
    combo_units->set_active(0); // default to "lbs"
    m_Grid.attach(*combo_units, 2, 0);

    // signal handler for empty mass dropdown
    combo_units->signal_changed().connect([this, entry_empty_weight, combo_units]() {
        std::string selected_unit = combo_units->get_active_text();
        if ((selected_unit == "kgs" && m_Emptymass.getUnits() == "lbs") ||
            (selected_unit == "lbs" && m_Emptymass.getUnits() == "kgs")) {
            m_Emptymass.convertUnits(); // convert units
            entry_empty_weight->set_text(std::to_string(m_Emptymass.getEmptyMass())); // update display
        }
    });

    //location label
    auto label_location = Gtk::make_managed<Gtk::Label>("Location(*)");
    m_Grid.attach(*label_location, 0, 3);

    //x coord label
    auto label_x = Gtk::make_managed<Gtk::Label>("x=");
    m_Grid.attach(*label_x, 0, 4);

    //x box
    auto entry_x = Gtk::make_managed<Gtk::Entry>();
    entry_x->set_editable(false);
    m_Grid.attach(*entry_x, 1, 4);
    entry_x->set_text(std::to_string(m_Location.getX()));

    //y coord label
    auto label_y = Gtk::make_managed<Gtk::Label>("y=");
    m_Grid.attach(*label_y, 2, 4);

    //y box
    auto entry_y = Gtk::make_managed<Gtk::Entry>();
    entry_x->set_editable(false);
    m_Grid.attach(*entry_y, 3, 4);
    entry_y->set_text(std::to_string(m_Location.getY()));

    //z coord label
    auto label_z = Gtk::make_managed<Gtk::Label>("z=");
    m_Grid.attach(*label_z, 4, 4);

    //z box
    auto entry_z = Gtk::make_managed<Gtk::Entry>();
    entry_x->set_editable(false);
    m_Grid.attach(*entry_z, 5, 4);
    entry_z->set_text(std::to_string(m_Location.getZ()));

    // location units dropdown
    auto combo_loc_units = Gtk::make_managed<Gtk::ComboBoxText>();
    combo_loc_units->append("in");
    combo_loc_units->append("cm");
    combo_loc_units->set_active(0); // Default to "in"
    m_Grid.attach(*combo_loc_units, 6, 4);

    // signal handler for length units dropdown
    combo_loc_units->signal_changed().connect([this, entry_x, entry_y, entry_z, combo_loc_units]() {
        std::string selected_unit = combo_loc_units->get_active_text();
        if ((selected_unit == "cm" && m_Location.getUnits() == "in") ||
            (selected_unit == "in" && m_Location.getUnits() == "cm")) {
                m_Location.convertLengthUnits(); 
                entry_x->set_text(std::to_string(m_Location.getX())); 
                entry_y->set_text(std::to_string(m_Location.getY())); 
                entry_z->set_text(std::to_string(m_Location.getZ())); 
    }
});

    //moment of inertia label
    auto label_moment_inertia = Gtk::make_managed<Gtk::Label>("Moment of inertia (*)");
    m_Grid.attach(*label_moment_inertia, 0, 5);

    //vector to implement inertia 
    std::vector<std::string> inertia_labels = {"Ixx", "Iyy", "Izz", "Ixz", "Iyz", "Ixy"};

    //calculate what column were iterating on
    int col1_row = 6; 
    int col2_row = 6; 
    int col = 0;      

    //for loop to added labels, entries, dropdowns (would have been easier to copy the code 6 times)
    for (size_t i = 0; i < inertia_labels.size(); ++i) {
    const auto& label = inertia_labels[i];

    if (i < 3) {
        col = 0;          // first column
        col1_row = 6 + i; // increment row for first column
    } else {
        col = 3;                // second column
        col2_row = 6 + (i - 3); // increment row for second column
    }

    // I** label
    auto inertia_label = Gtk::make_managed<Gtk::Label>(label + " = ");
    m_Grid.attach(*inertia_label, col, (col == 0 ? col1_row : col2_row));

    // Entry box
    auto entry_inertia = Gtk::make_managed<Gtk::Entry>();
    entry_inertia->set_editable(false);
    m_Grid.attach(*entry_inertia, col + 1, (col == 0 ? col1_row : col2_row));

    // Set initial inertia value
    double inertia_value = 0.0;
    if (label == "Ixx") {
        inertia_value = m_airplane.totalInertiaAboutLongitudinalAxis();
    } else if (label == "Iyy") {
        inertia_value = m_airplane.totalInertiaAboutTransverseAxis();
    } else if (label == "Izz") {
        inertia_value = m_airplane.totalInertiaAboutVerticalAxis();
    } else {
        inertia_value = 0.0; // Default to 0 for off-diagonal terms (Ixz, Iyz, Ixy)
    }
    entry_inertia->set_text(std::to_string(inertia_value));

    // Dropdown
    auto combo_inertia_units = Gtk::make_managed<Gtk::ComboBoxText>();
    combo_inertia_units->append("SLUG*FT2");
    combo_inertia_units->append("KG*M2");
    combo_inertia_units->set_active(0); // Default to "SLUG*FT2"
    m_Grid.attach(*combo_inertia_units, col + 2, (col == 0 ? col1_row : col2_row));

    // Signal for each dropdown
    combo_inertia_units->signal_changed().connect([entry_inertia, combo_inertia_units, m_airplane]() mutable {
        std::string selected_unit = combo_inertia_units->get_active_text();
        if ((selected_unit == "KG*M2" && m_airplane.getInertiaUnits() == "SLUG*FT2") ||
            (selected_unit == "SLUG*FT2" && m_airplane.getInertiaUnits() == "KG*M2")) {
            m_airplane.convertInertiaUnits(); // Convert units
        }
        entry_inertia->set_text(std::to_string(m_airplane.totalInertiaAboutLongitudinalAxis())); // Update display
    });
}
    
        //point mass label
        auto label_point_mass = Gtk::make_managed<Gtk::Label>("Point mass");
        m_Grid.attach(*label_point_mass, 0, 9);
        
        //entry point mass
        auto entry_point_mass = Gtk::make_managed<Gtk::Entry>();
        entry_point_mass->set_editable(false);
        entry_point_mass->set_vexpand(true);
        m_Grid.attach(*entry_point_mass, 0, 10, 8, 4);

        //button to add a new point mass
        auto button_new_mass = Gtk::make_managed<Gtk::Button>("Add a new point mass");
        m_Grid.attach(*button_new_mass, 0, 14, 4, 1); 

        //button to delete selected point mass
        auto button_del_mass = Gtk::make_managed<Gtk::Button>("Delete the selected point mass");
        m_Grid.attach(*button_del_mass, 4, 14, 4, 1); 
    
}

