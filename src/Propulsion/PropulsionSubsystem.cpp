#include <iostream>
#include <vector>  // For buttonNames
#include <map>     // For buttonMap
#include <utility> // For std::pair
#include <filesystem> // For file operations
#include <cstdlib> // For GetCurrentPlatform

#include "PropulsionSubsystem.hpp"
#include "PropulsionManager.hpp"
#include "EngineSelectorWindow.hpp"

namespace fs = std::filesystem;

/*PropulsionSubsystem::PropulsionSubsystem() {
    m_Name = "Propulsion";
    std::cout << "In PropulsionSubsystem constructor" << std::endl;
}*/

PropulsionSubsystem::PropulsionSubsystem(Gtk::Window& parent) 
    : Gtk::Window(), m_PropManager(parent) {}


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

    // Rudimentary File Logic to get names of files in data/engine
    // NOTE: NOT XML LOGIC
    // TODO: Function to check if Engine or Thruster
    // Path to the directory
    std::string basePath = fs::current_path().string();
    std::string dirpath = basePath + "/jsbsimedit/data/engine";

    // Define the part to remove from the path
    std::string toRemove = "/jsbsimedit/out/build/";

    toRemove += GetCurrentPlatform();

    // if Mac: MacOS-Arm64-Clang-Debug
    // if Windows: Windows-x64-Clang-Debug
    // if Linux: Linux-x64-GCC-Debug
    
    // Find the position of the part to remove
    size_t pos = dirpath.find(toRemove);
    if (pos != std::string::npos) {
        // Remove the specified part from the path
        dirpath.erase(pos, toRemove.length());
    }

    // Now you can use this path to access the directory
    if (fs::exists(dirpath) && fs::is_directory(dirpath)) {
        for (const auto& entry : fs::directory_iterator(dirpath)) {
            if (entry.is_regular_file()) {
                std::cout << "File: " << entry.path().filename() << std::endl;
            }
        }
    } else {
        std::cerr << "Directory does not exist: " << dirpath << std::endl;
    }
    

    pComboBoxEng->append("No Selection");

    if (fs::exists(dirpath) && fs::is_directory(dirpath)) {
        for (const auto& entry : fs::directory_iterator(dirpath)) {
            if (entry.is_regular_file()) {
                // Get the filename as a string
                std::string filename = entry.path().filename().string();
                
                // Check if the filename ends with ".xml" and remove it
                if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".xml") {
                    filename = filename.substr(0, filename.size() - 4);  // Remove the ".xml" extension
                }

                // Add the filename (without .xml) to the dropdown
                pComboBoxEng->append(filename);
            }
        }
    } else {
        std::cerr << "Directory does not exist: " << dirpath << std::endl;
    }
    
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
                //Tank myTank(fuelType, tankCapacity, tankFillValue);  // Replace with actual values
                m_PropManager.showTankSetup();         // Pass the required arguments

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

    if ((inp == "No Selection") || (inp == "")) {
        // TODO: Make popup if user inputs invalid selection 
        std::cout << "Invalid Selection for button, Please reselect!" << std::endl;
        return false;
    } else {
        std::cout << "Input:" << inp << "Valid Selection for button!" << std::endl;
        return true;
    }


    return false;
}

std::string PropulsionSubsystem::GetCurrentPlatform() {
    #ifdef _WIN32
        return "Windows-x64-Clang-Debug"; // Windows
    #elif defined(__APPLE__) && defined(__MACH__)
        return "MacOS-Arm64-Clang-Debug"; // macOS
    #elif defined(__linux__)
        return "Linux-x64-GCC-Debug"; // Linux
    #else
        return "Unknown";
    #endif
}

