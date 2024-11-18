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

    // Engine UI
    Gtk::Label* pLabelEng = Gtk::make_managed<Gtk::Label>("Select Engine:");
    // Create the ComboBoxText (dropdown menu) for engine selection
    Gtk::ComboBoxText* pComboBoxEng = Gtk::make_managed<Gtk::ComboBoxText>();
    // TODO: Replace with xml logic to find engines
    pComboBoxEng->append("AJ26-33A");
    pComboBoxEng->append("GE-CF6-80C2-B1F");
    pComboBoxEng->append("electric_1mw");

    // Set default selection
    pComboBoxEng->set_active(0); // Default to first option "AJ26-33A"

    // Connect signal to handle dropdown changes
    pComboBoxEng->signal_changed().connect([this, pComboBoxEng]() {
        std::string selectedEngine = pComboBoxEng->get_active_text();
        std::cout << "Selected Engine: " << selectedEngine << std::endl;
    });
    m_Grid.attach(*pLabelEng, 0, 0, 1, 1);  // Label: row 0, column 0
    m_Grid.attach(*pComboBoxEng, 0, 1, 1, 1);  // ComboBox: row 1, column 0
    
    
    // Thruster UI
    Gtk::Label* pLabelThr = Gtk::make_managed<Gtk::Label>("Select Thruster:");
    // Create the ComboBoxText (dropdown menu) for thruster selection
    Gtk::ComboBoxText* pComboBoxThr = Gtk::make_managed<Gtk::ComboBoxText>();
    // TODO: Replace with xml logic to find Thrusters
    pComboBoxThr->append("PLACEHOLDER_Thruster");
    pComboBoxThr->append("PLACEHOLDER_Thruster");
    pComboBoxThr->append("PLACEHOLDER_Thruster");

    // Set default selection
    pComboBoxThr->set_active(0); 

    // Connect signal to handle dropdown changes
    pComboBoxThr->signal_changed().connect([this, pComboBoxThr]() {
        std::string selectedThruster = pComboBoxThr->get_active_text();
        std::cout << "Selected Thruster: " << selectedThruster << std::endl;
    });
    m_Grid.attach(*pLabelThr, 0, 2, 1, 1);  // Label: row 0, column 0
    m_Grid.attach(*pComboBoxThr, 0, 3, 1, 1);  // ComboBox: row 1, column 0
    


    // Tank UI
    Gtk::Label* pLabelTK = Gtk::make_managed<Gtk::Label>("Select Tank:");
    // Create the ComboBoxText (dropdown menu) for Tank selection
    Gtk::ComboBoxText* pComboBoxTK = Gtk::make_managed<Gtk::ComboBoxText>();
    // TODO: Replace with xml logic to find Tanks
    // Placeholders
    pComboBoxTK->append("FULL TANK 1000 GALLONS");
    pComboBoxTK->append("NFULL TANK 1000 GALLONS");
    pComboBoxTK->append("PLACEHOLDER");

    // Set default selection
    pComboBoxTK->set_active(0); 

    // Connect signal to handle dropdown changes
    pComboBoxTK->signal_changed().connect([this, pComboBoxTK]() {
        std::string selectedTank = pComboBoxTK->get_active_text();
        std::cout << "Selected Tank: " << selectedTank << std::endl;
    });
    m_Grid.attach(*pLabelTK, 1, 0, 1, 1);  // Label: row 1, column 0
    m_Grid.attach(*pComboBoxTK, 1, 1, 1, 1);  // ComboBox: row 1, column 1


    // i is length #, j is height #
    for (int i = 2; i < 4; i++) { // Shifts buttons to columns 2 and 3
        for (int j = 1; j < 4; j++) { // Lowered buttons to row 1 through 3
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
    pLabelEng->show();  // Show the label
    pLabelThr->show();  // Show the label
    pLabelTK->show();  // Show the label

    pComboBoxEng->show();  // Show the combo box
    pComboBoxThr->show();  // Show the combo box
    pComboBoxTK->show();  // Show the combo box

    for (auto& buttonPair : buttonMap) {
        buttonPair.second->show();  // Show each button in the map
    }
}
