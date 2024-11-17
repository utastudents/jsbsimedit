#include "EngineSelectorWindow.hpp"
#include <iostream>  // For std::cout

EngineSelectorWindow::EngineSelectorWindow() {
    // Set up window properties
    set_title("Engine Selector");
    set_default_size(300, 200);  // Set the window's size

    // Create and set label text
    m_Label.set_text("Select Engine:");

    // Create ComboBoxText for engine selection
    m_ComboBox.append("AJ26-33A");
    m_ComboBox.append("GE-CF6-80C2-B1F");
    m_ComboBox.append("electric_1mw");
    m_ComboBox.set_active(0);  // Default selection

    // Connect signal for selection change
    m_ComboBox.signal_changed().connect([this]() {
        std::string selected = m_ComboBox.get_active_text();
        std::cout << "Selected engine: " << selected << std::endl;  // Output selected engine
        });

    // Create a button to close the window
    m_Button.set_label("Close");
    m_Button.signal_clicked().connect(sigc::mem_fun(*this, &EngineSelectorWindow::on_button_clicked));

    // Set up grid layout
    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);
    m_Grid.attach(m_Label, 0, 0, 2, 1);   // Attach label to grid
    m_Grid.attach(m_ComboBox, 0, 1, 2, 1); // Attach combo box to grid
    m_Grid.attach(m_Button, 0, 2, 2, 1);   // Attach button to grid

    // Set the grid as the window's child widget using set_child()
    set_child(m_Grid);  // Set the main layout container (grid) for the window

    // Explicitly show the widgets individually (no show_all_children())
    m_Label.show();
    m_ComboBox.show();
    m_Button.show();
    m_Grid.show();  // Ensure the grid itself is shown
}

void EngineSelectorWindow::on_button_clicked() {
    std::cout << "Button clicked, closing the window." << std::endl;  // Output when button is clicked
    hide();  // Hide the window when the button is clicked
}
