#include <iostream>
#include <vector>  // For buttonNames
#include <map>     // For buttonMap
#include <utility> // For std::pair
#include <filesystem> // For `operations
#include <cstdlib> // For GetCurrentPlatform

#include "inc/XML_api.hpp"

#include "PropulsionSubsystem.hpp"
#include "PropulsionManager.hpp"
#include "EngineSelectorWindow.hpp"
#include "EngineThrusterDialog.hpp"

PropulsionManager m_PropManager;  // Propulsion manager instance

namespace fs = std::filesystem;

PropulsionSubsystem::PropulsionSubsystem() {
    m_Name = "Propulsion";
    std::cout << "In PropulsionSubsystem constructor" << std::endl;
}
std::string PropulsionSubsystem::getSelectedEngine() const {
    return std::string(selectedEngine);
}
std::string PropulsionSubsystem::getSelectedThruster() const {
    return std::string(selectedThruster);
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

    // Thruster UI
    Gtk::Label* pLabelThr = Gtk::make_managed<Gtk::Label>("Select Thruster:");
    // Create the ComboBoxText (dropdown menu) for thruster selection
    Gtk::ComboBoxText* pComboBoxThr = Gtk::make_managed<Gtk::ComboBoxText>();    

    // Rudimentary File Logic to get names of files in data/engine
    // NOTE: NOT XML LOGIC
    // TODO: Function to check if Engine or Thruster
    // Path to the directory
    std::string basePath = fs::current_path().string();
    std::string dirpath = basePath + "/jsbsimedit/data/engine";

    // Define the part to remove from the path
    std::string toRemove = "/jsbsimedit/out/build/";

    toRemove += GetCurrentPlatformDebug();

    // TEMP SOLUTION FIX BEFORE LAUNCH
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
    
    std::vector<std::string> combinedList = {
        "piston_engine",
        "rocket_engine",
        "turboprop_engine",
        "electric_engine",
        "turbine_engine",
        "propeller",
        "FG_NOZZLE",
        "FG_ROCKET",
        "rotor",
        "nozzle"
    };

    pComboBoxEng->append("No Selection");
    pComboBoxThr->append("No Selection");

    if (fs::exists(dirpath) && fs::is_directory(dirpath)) {
        for (const auto& entry : fs::directory_iterator(dirpath)) {
            if (entry.is_regular_file()) {
                // Get the filename as a string
                std::string filepath = entry.path().string();

                // XML Logic
                // Parse the XML file
                xmlptr()->LoadFileAndParse(filepath);
        
                JSBEdit::XMLNode rootNode = xmlptr()->GetNode(""); // Get the document's root node
                rootNode = rootNode.GetParent(); // Traverse up to the root node
                // Extract the name of the root element
                std::string rootElement = rootNode.GetName();
                size_t index = 0;  // Index for iterating through the list

                while (rootElement == "" && index < combinedList.size()) {
                    rootNode = xmlptr()->GetNode(combinedList[index]);  // Set rootElement to the current item in the list
                    rootElement = rootNode.GetName();
                    index++;  // Move to the next item in the list
                }

                std::cout << "rootElement: " << rootElement << std::endl;
                std::string type = EngineOrThruster(rootElement);

                // Handle the result from EngineOrThruster
                if (type == "engine") {
                    std::cout << "Added to engine dropdown: " << entry.path().stem().string() << std::endl;
                    pComboBoxEng->append(entry.path().stem().string()); // Add filename without extension
                } else if (type == "thruster") {
                    std::cout << "Added to thruster dropdown: " << entry.path().stem().string() << std::endl;
                    pComboBoxThr->append(entry.path().stem().string()); // Add filename without extension
                } else {
                    std::cout << "File does not match any known type: " << entry.path().stem().string() << std::endl;
                }
            }
        }
    } else {
        std::cerr << "Directory does not exist: " << dirpath << std::endl;
    }
    
    // Engine dropdown
    pComboBoxEng->set_active(0); // Default to first option "No Selection"
    // Connect signal to handle dropdown changes
    pComboBoxEng->signal_changed().connect([this, pComboBoxEng]() {
        this->selectedEngine = pComboBoxEng->get_active_text();
        std::cout << "Selected Engine: " << this->selectedEngine << std::endl;
    });
    m_Grid.attach(*pLabelEng, 0, 0, 1, 1);  // Label: row 0, column 0
    m_Grid.attach(*pComboBoxEng, 0, 1, 1, 1);  // ComboBox: row 1, column 0
    
    // Thruster dropdown
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
                auto reselectdialog = Gtk::make_managed<Gtk::MessageDialog>(
                "Engine/Thruster not selected from dropdowns, please select before creating.",
                false, Gtk::MessageType::WARNING, Gtk::ButtonsType::OK, true);
                reselectdialog->set_title("Selection Required");
                reselectdialog->signal_response().connect([reselectdialog](int) {
                    reselectdialog->hide();
                });
                reselectdialog->show();
            }   
        }, 
        [this]() { // "Engine/Thruster Pair Details"
            if ((checkSelect(selectedEngine)==true) && (checkSelect(selectedThruster)==true)) {// Engine/Thruster select check
                m_PropManager.showEngineThrusterSetup();
            } else if ((checkSelect(selectedEngine)!=true) || (checkSelect(selectedThruster)!=true)) {
                auto reselectdialog = Gtk::make_managed<Gtk::MessageDialog>(
                "Engine/Thruster not selected from dropdowns, please select before altering.",
                false, Gtk::MessageType::WARNING, Gtk::ButtonsType::OK, true);
                reselectdialog->set_title("Selection Required");
                reselectdialog->signal_response().connect([reselectdialog](int) {
                    reselectdialog->hide();
                });
                reselectdialog->show();
            }   
        }, 
        [this]() { // "Delete Engine/Thruster Pair"
            auto dialog = Gtk::make_managed<Gtk::MessageDialog>(
                "Are you sure you want to delete the selected engine/thruster pair?",
                false, Gtk::MessageType::QUESTION, Gtk::ButtonsType::YES_NO, true);
            dialog->set_title("Delete Engine/Thruster Pair Confirmation");
            dialog->signal_response().connect([this, dialog](int response_id) {
                if (response_id == Gtk::ResponseType::YES) {
                    m_PropManager.confirmDeletePair();
                    std::cout << "Engine/Thruster pair deleted successfully!" << std::endl;
                } else {
                    std::cout << "Engine/Thruster pair deletion canceled." << std::endl;
                }
                dialog->close();
            });
            dialog->show();
        },
        [this]() { // "Create Tank"
            // TODO: When tank is created append it to list of tank options
            m_PropManager.showTankSetup(); 
        }, 
        [this]() { // "Tank Details"
            if ((checkSelect(selectedTank)==true)) {// Tank select check
                m_PropManager.showTankSetup(); 
            } else if ((checkSelect(selectedTank)!=true)) {
                auto reselectdialog = Gtk::make_managed<Gtk::MessageDialog>(
                "Existing Tank not selected from dropdowns, please select before altering.",
                false, Gtk::MessageType::WARNING, Gtk::ButtonsType::OK, true);
                reselectdialog->set_title("Selection Required");
                reselectdialog->signal_response().connect([reselectdialog](int) {
                    reselectdialog->hide();
                });
                reselectdialog->show();
            }   
        },
        [this]() { // "Delete Tank"
            if ((checkSelect(selectedTank)==true)) { // Check confirming tank is selected vefore calling confirm Delete Tank
                auto dialog = Gtk::make_managed<Gtk::MessageDialog>(
                    "Are you sure you want to delete the selected tank?",
                    false, Gtk::MessageType::QUESTION, Gtk::ButtonsType::YES_NO, true);
                dialog->set_title("Delete Tank Confirmation");
                dialog->signal_response().connect([this, dialog](int response_id) {
                    if (response_id == Gtk::ResponseType::YES) {
                        m_PropManager.confirmDeleteTank();
                        std::cout << "Tank deleted successfully!" << std::endl;
                    } else {
                        std::cout << "Tank deletion canceled." << std::endl;
                    }
                    dialog->close();
                });
                dialog->show();
            }
            else if ((checkSelect(selectedTank)!=true)) {
                auto reselectdialog = Gtk::make_managed<Gtk::MessageDialog>(
                "Existing Tank not selected from dropdowns, please select before altering.",
                false, Gtk::MessageType::WARNING, Gtk::ButtonsType::OK, true);
                reselectdialog->set_title("Selection Required");
                reselectdialog->signal_response().connect([reselectdialog](int) {
                    reselectdialog->hide();
                });
                reselectdialog->show();
            }   
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

std::string PropulsionSubsystem::EngineOrThruster(const std::string& pulledInput) {
    // List of engine types in xml
    std::vector<std::string> enginetype = {
        "piston_engine",
        "rocket_engine",
        "turboprop_engine",
        "electric_engine",
        "turbine_engine"
    };

    // List of thruster types in xml
    std::vector<std::string> thrustertype = {
        "propeller",
        "FG_NOZZLE",
        "FG_ROCKET",
        "rotor",
        "nozzle"
    };

    // Flag to indicate a match, True if match found
    bool matchFound = false;
    std::string output = "BLANK";

    // Combined loop for both lists
    for (const auto& engine : enginetype) {
        if (pulledInput == engine) {
            matchFound = true;
            std::cout << "Match found in enginetype: " << engine << std::endl;
            output = "engine";
            return output;

        }
    }

    if (!matchFound) {
        for (const auto& thruster : thrustertype) {
            if (pulledInput == thruster) {
                matchFound = true;
                std::cout << "Match found in thrustertype: " << thruster << std::endl;
                output = "thruster";
                return output;
            }
        }
    }

    else if (!matchFound) {
        std::cout << "No match found.\n";
        output = "BLANK";
    }

    // return either engine or thruster as string
    return output;
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
// TEMP SOLUTION FIX BEFORE LAUNCH
// Gets Debug version on an OS basis
std::string PropulsionSubsystem::GetCurrentPlatformDebug() {
    #ifdef _WIN32
        return "Windows-x64-Clang-Debug"; // Windows
    #elif defined(__APPLE__) && defined(__MACH__)
        return "MacOS-Arm64-Clang-Debug"; // macOS
    #elif defined(__linux__)
        return "Linux-x64-Clang-Debug"; // Linux
    #else
        return "Unknown";
    #endif
}
