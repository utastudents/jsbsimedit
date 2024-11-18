#include <iostream>
#include <vector>  // For buttonNames
#include <map>     // For buttonMap
#include <utility> // For std::pair
#include "PropulsionSubsystem.hpp"
#include "PropulsionManager.hpp"
#include "EngineSelectorWindow.hpp"

PropulsionSubsystem::PropulsionSubsystem() {
    m_Name = "Propulsion";
    std::cout << "In PropulsionSubsystem constructor" << std::endl;
}

void PropulsionSubsystem::Create() {
    std::cout << "in PropulsionSubsystem::Create" << std::endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    std::map<std::pair<int, int>, Gtk::Button*> buttonMap;

    // Separated line of code for readability
    std::vector<std::string> buttonNames = {
        // Engine Thruster Button Names
        "Create Engine/Thruster Pair", "Engine/Thruster Pair Details", "Delete Engine/Thruster Pair",
        // Tank Button Names
        "Create Tank", "Tank Details", "Delete Tank"
    };

    int nameIndex = 0;

    // Define the unique actions for each button in lambdas
    std::vector<std::function<void()>> buttonActions = {
        [this]() { m_PropManager.showEngineThrusterSetup(); }, // "Create Engine/Thruster Pair"
        [this]() { m_PropManager.showEngineThrusterSetup(); }, // "Engine/Thruster Pair Details"
        [this]() { m_PropManager.confirmDeletePair(); }, // "Delete Engine/Thruster Pair"
        [this]() { m_PropManager.showTankSetup(); }, // "Create Tank"
        [this]() { m_PropManager.showTankSetup(); }, // "Tank Details"
        [this]() { m_PropManager.confirmDeleteTank(); } // "Delete Tank"
    };

    // Create a label for the engine selection dropdown
    Gtk::Label* pLabel = Gtk::make_managed<Gtk::Label>("Select Engine:");

    // Create the ComboBoxText (dropdown menu) for engine selection
    Gtk::ComboBoxText* pComboBox = Gtk::make_managed<Gtk::ComboBoxText>();
    // TODO: Replace with xml logic to find 
    pComboBox->append("AJ26-33A");
    pComboBox->append("GE-CF6-80C2-B1F");
    pComboBox->append("electric_1mw");

    // Set default selection
    pComboBox->set_active(0); // Default to first option "AJ26-33A"

    // Connect signal to handle dropdown changes
    pComboBox->signal_changed().connect([this, pComboBox]() {
        std::string selectedEngine = pComboBox->get_active_text();
        std::cout << "Selected Engine: " << selectedEngine << std::endl;
    });

    // Attach the label and ComboBoxText to the grid (Place the label at row 0, column 3, and the ComboBox at row 1, column 3)
    m_Grid.attach(*pLabel, 0, 0, 1, 1);  // Label: row 0, column 0
    m_Grid.attach(*pComboBox, 0, 1, 1, 1);  // ComboBox: row 1, column 0

    // i is length #, j is height #
    for (int i = 1; i < 3; i++) { // Shifts buttons to columns 1 and 2
        for (int j = 0; j < 3; j++) {
            if (nameIndex < buttonNames.size()) {
                // Create each button with a unique name
                auto pButton = Gtk::make_managed<Gtk::Button>(buttonNames[nameIndex]);
                m_Grid.attach(*pButton, i, j);  // Place in grid (i, j) to fill bottom-right

                // Store Buttons in map for accessibility
                buttonMap[{i, j}] = pButton;

                // Connect each button's signal to its specific lambda function
                pButton->signal_clicked().connect(buttonActions[nameIndex]);

                // Move to the next name
                nameIndex++;
            }
        }
    }

    m_Grid.show();  // Show the grid container
    // Show each individual widget explicitly
    pLabel->show();  // Show the label
    pComboBox->show();  // Show the combo box
    for (auto& buttonPair : buttonMap) {
        buttonPair.second->show();  // Show each button in the map
    }
}
