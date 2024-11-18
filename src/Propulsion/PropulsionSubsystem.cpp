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


    // Engine UI
    Gtk::Label* pLabelEng = Gtk::make_managed<Gtk::Label>("Select Engine:");
    // Create the ComboBoxText (dropdown menu) for engine selection
    Gtk::ComboBoxText* pComboBoxEng = Gtk::make_managed<Gtk::ComboBoxText>();
    // TODO: Replace with xml logic to find engines
    pComboBoxEng->append("No Selection");
    pComboBoxEng->append("AJ26-33A");
    pComboBoxEng->append("GE-CF6-80C2-B1F");
    pComboBoxEng->append("electric_1mw");

    // Set default selection
    pComboBoxEng->set_active(0); // Default to first option "No Selection"

    // Connect signal to handle dropdown changes
    pComboBoxEng->signal_changed().connect([this, pComboBoxEng]() {
        this->selectedEngine = pComboBoxEng->get_active_text();
        std::cout << "Selected Engine: " << this->selectedEngine << std::endl;
    });
    m_Grid.attach(*pLabelEng, 0, 0, 1, 1);  // Label: row 0, column 0
    m_Grid.attach(*pComboBoxEng, 0, 1, 1, 1);  // ComboBox: row 1, column 0
    
    
    // Thruster UI
    Gtk::Label* pLabelThr = Gtk::make_managed<Gtk::Label>("Select Thruster:");
    // Create the ComboBoxText (dropdown menu) for thruster selection
    Gtk::ComboBoxText* pComboBoxThr = Gtk::make_managed<Gtk::ComboBoxText>();
    // TODO: Replace with xml logic to find Thrusters
    pComboBoxThr->append("No Selection");
    pComboBoxThr->append("PLACEHOLDER_Thruster");
    pComboBoxThr->append("PLACEHOLDER_Thruster");
    pComboBoxThr->append("PLACEHOLDER_Thruster");

    // Set default selection
    pComboBoxThr->set_active(0); 

    // Connect signal to handle dropdown changes
    pComboBoxThr->signal_changed().connect([this, pComboBoxThr]() {
        this->selectedThruster = pComboBoxThr->get_active_text();
        std::cout << "Selected Thruster: " << this->selectedThruster << std::endl;
    });
    m_Grid.attach(*pLabelThr, 0, 2, 1, 1);  // Label: row 0, column 0
    m_Grid.attach(*pComboBoxThr, 0, 3, 1, 1);  // ComboBox: row 1, column 0
    


    // Tank UI
    Gtk::Label* pLabelTK = Gtk::make_managed<Gtk::Label>("Select Tank:");
    // Create the ComboBoxText (dropdown menu) for Tank selection
    Gtk::ComboBoxText* pComboBoxTK = Gtk::make_managed<Gtk::ComboBoxText>();
    // TODO: Replace with xml logic to find Tanks
    // Placeholders
    pComboBoxTK->append("No Selection");
    pComboBoxTK->append("FULL TANK 1000 GALLONS");
    pComboBoxTK->append("NFULL TANK 1000 GALLONS");
    pComboBoxTK->append("PLACEHOLDER");

    // Set default selection
    pComboBoxTK->set_active(0); 

    // Connect signal to handle dropdown changes
    pComboBoxTK->signal_changed().connect([this, pComboBoxTK]() {
        this->selectedTank = pComboBoxTK->get_active_text();
        std::cout << "Selected Engine: " << this->selectedTank << std::endl;
    });
    m_Grid.attach(*pLabelTK, 1, 0, 1, 1);  // Label: row 1, column 0
    m_Grid.attach(*pComboBoxTK, 1, 1, 1, 1);  // ComboBox: row 1, column 1


    // Define the unique actions for each button in lambdas
    std::vector<std::function<void()>> buttonActions = {
        [this]() { // "Create Engine/Thruster Pair"
            // TODO: When Engine/Thruster Pair is created append it to list of Engine/Thruster Pair options
            if ((checkSelect(selectedEngine)==true) && (checkSelect(selectedThruster)==true)) {// Engine/Thruster select check
                m_PropManager.showEngineThrusterSetup(); 
            } else if ((checkSelect(selectedEngine)!=true) || (checkSelect(selectedThruster)!=true)) {
                // TODO: Reselect popup goes here
                std::cout << "Reselect popup goes here" << std::endl;
            }
        }, 
        [this]() { // "Engine/Thruster Pair Details"
            if ((checkSelect(selectedEngine)==true) && (checkSelect(selectedThruster)==true)) {// Engine/Thruster select check
                m_PropManager.showEngineThrusterSetup();
            } else if ((checkSelect(selectedEngine)!=true) || (checkSelect(selectedThruster)!=true)) {
                // TODO: Reselect popup goes here
                std::cout << "Reselect popup goes here" << std::endl;
            }
        }, 
        [this]() { // "Delete Engine/Thruster Pair"
            // TODO: When Engine/Thruster Pair is deleted remove it from list of Engine/Thruster Pair options
            m_PropManager.confirmDeletePair(); 
        }, 
        [this]() { // "Create Tank"
            // TODO: When tank is created append it to list of tank options
            if (checkSelect(selectedTank)==true) {
                m_PropManager.showTankSetup(); 
            } else if (checkSelect(selectedTank)!=true){
                // TODO: Reselect popup goes here
                std::cout << "Reselect popup goes here" << std::endl;
            }        
        }, 
        [this]() { // "Tank Details"
            if (checkSelect(selectedTank)==true) {
                m_PropManager.showTankSetup(); 
            } else if (checkSelect(selectedTank)!=true){
                // TODO: Reselect popup goes here
                std::cout << "Reselect popup goes here" << std::endl;
            }
        },
        [this]() { // "Delete Tank"
            // TODO: When tank is deleted remove it from list of tank options
            m_PropManager.confirmDeleteTank(); 
        } 
    };


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

bool PropulsionSubsystem::checkSelect(const std::string& inp) {
    // If checkSelect returns False one of the users inputs is invalid and must be changed
    // TODO: Make popup if user inputs invalid selection 

    if (inp == "No Selection") {
        // TODO: Make popup if user inputs invalid selection 
        std::cout << "Invalid Selection for button, Please reselect!" << std::endl;
        return false;
    } else {
        std::cout << "Valid Selection for button!" << std::endl;
        return true;
    }


    return false;
}