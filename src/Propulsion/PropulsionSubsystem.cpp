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

PropulsionSubsystem::PropulsionSubsystem() {
    m_Name = "Propulsion";
    std::cout << "In PropulsionSubsystem constructor" << std::endl;
}

void PropulsionSubsystem::Create() {
    std::cout << "in PropulsionSubsystem::Create" << std::endl;

    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    std::map<std::pair<int, int>, Gtk::Button*> buttonMap;

    std::vector<std::string> buttonNames = {
        "Create Engine/Thruster Pair", "Engine/Thruster Pair Details", "Delete Engine/Thruster Pair",
        "Create Tank", "Tank Details", "Delete Tank"
    };

    int nameIndex = 0;

    // Engine UI
    Gtk::Label* pLabelEng = Gtk::make_managed<Gtk::Label>("Select Engine:");
    Gtk::ComboBoxText* pComboBoxEng = Gtk::make_managed<Gtk::ComboBoxText>();

    std::string basePath = fs::current_path().string();
    std::string dirpath = basePath + "/jsbsimedit/data/engine";
    std::string toRemove = "/jsbsimedit/out/build/";

    toRemove += GetCurrentPlatformDebug();

    size_t pos = dirpath.find(toRemove);
    if (pos != std::string::npos) {
        dirpath.erase(pos, toRemove.length());
    }

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
                std::string filename = entry.path().filename().string();
                if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".xml") {
                    filename = filename.substr(0, filename.size() - 4);
                }
                pComboBoxEng->append(filename);
            }
        }
    } else {
        std::cerr << "Directory does not exist: " << dirpath << std::endl;
    }

    pComboBoxEng->set_active(0);
    pComboBoxEng->signal_changed().connect([this, pComboBoxEng]() {
        this->selectedEngine = pComboBoxEng->get_active_text();
        std::cout << "Selected Engine: " << this->selectedEngine << std::endl;
    });
    m_Grid.attach(*pLabelEng, 0, 0, 1, 1);
    m_Grid.attach(*pComboBoxEng, 0, 1, 1, 1);

    // Thruster UI
    Gtk::Label* pLabelThr = Gtk::make_managed<Gtk::Label>("Select Thruster:");
    Gtk::ComboBoxText* pComboBoxThr = Gtk::make_managed<Gtk::ComboBoxText>();
    pComboBoxThr->append("No Selection");
    pComboBoxThr->append("PLACEHOLDER_Thruster");
    pComboBoxThr->append("PLACEHOLDER_Thruster");
    pComboBoxThr->append("PLACEHOLDER_Thruster");
    pComboBoxThr->set_active(0);
    pComboBoxThr->signal_changed().connect([this, pComboBoxThr]() {
        this->selectedThruster = pComboBoxThr->get_active_text();
        std::cout << "Selected Thruster: " << this->selectedThruster << std::endl;
    });
    m_Grid.attach(*pLabelThr, 0, 2, 1, 1);
    m_Grid.attach(*pComboBoxThr, 0, 3, 1, 1);

    // Tank UI
    Gtk::Label* pLabelTK = Gtk::make_managed<Gtk::Label>("Select Tank:");
    Gtk::ComboBoxText* pComboBoxTK = Gtk::make_managed<Gtk::ComboBoxText>();
    pComboBoxTK->append("No Selection");
    pComboBoxTK->append("FULL TANK 1000 GALLONS");
    pComboBoxTK->append("NFULL TANK 1000 GALLONS");
    pComboBoxTK->append("PLACEHOLDER");
    pComboBoxTK->set_active(0);
    pComboBoxTK->signal_changed().connect([this, pComboBoxTK]() {
        this->selectedTank = pComboBoxTK->get_active_text();
        std::cout << "Selected Tank: " << this->selectedTank << std::endl;
    });
    m_Grid.attach(*pLabelTK, 1, 0, 1, 1);
    m_Grid.attach(*pComboBoxTK, 1, 1, 1, 1);

    // Button actions
    std::vector<std::function<void()>> buttonActions = {
        [this]() { /* Create Engine/Thruster Pair Logic */ },
        [this]() { /* Engine/Thruster Pair Details Logic */ },
        [this]() { /* Delete Engine/Thruster Pair Logic */ },
        [this]() { m_PropManager.showTankSetup(); },
        [this]() { m_PropManager.showTankSetup(); },
        [this]() { 
            // **NEW: Delete Tank with Confirmation Dialog**
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
    };

    for (int i = 2; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (nameIndex < buttonNames.size()) {
                auto pButton = Gtk::make_managed<Gtk::Button>(buttonNames[nameIndex]);
                m_Grid.attach(*pButton, i, j);
                buttonMap[{i, j}] = pButton;
                pButton->signal_clicked().connect(buttonActions[nameIndex]);
                nameIndex++;
            }
        }
    }

    m_Grid.show();
    pLabelEng->show();
    pLabelThr->show();
    pLabelTK->show();
    pComboBoxEng->show();
    pComboBoxThr->show();
    pComboBoxTK->show();

    for (auto& buttonPair : buttonMap) {
        buttonPair.second->show();
    }
}

bool PropulsionSubsystem::checkSelect(const std::string& inp) {
    if ((inp == "No Selection") || (inp == "")) {
        std::cout << "Invalid Selection for button, Please reselect!" << std::endl;
        return false;
    } else {
        std::cout << "Input:" << inp << "Valid Selection for button!" << std::endl;
        return true;
    }
    return false;
}

std::string PropulsionSubsystem::GetCurrentPlatformDebug() {
    #ifdef _WIN32
        return "Windows-x64-Clang-Debug";
    #elif defined(__APPLE__) && defined(__MACH__)
        return "MacOS-Arm64-Clang-Debug";
    #elif defined(__linux__)
        return "Linux-x64-Clang-Debug";
    #else
        return "Unknown";
    #endif
}
