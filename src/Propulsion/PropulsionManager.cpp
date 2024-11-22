#include "PropulsionManager.hpp"
#include "EngineThrusterDialog.hpp"
#include "TankDialog.hpp"
#include <gtkmm.h>
#include <iostream>
#include "Tank.hpp"
#include "../MainWindow/ExampleWindow.hpp"  // Adjust the path if needed


void PropulsionManager::showEngineThrusterSetup() { 
    // TODO: Confirm if 1st time setup
    // TODO: Implement engine/thruster setup display
    
    EngineThrusterDialog dialogEng;
    std::cout << "Displaying engine/thruster setup..." << std::endl;
}

/*void PropulsionManager::showTankSetup() {
    // TODO: Implement tank setup display

    TankDialog dialogTK;
    std::cout << "Displaying tank setup..." << std::endl;
}*/

void PropulsionManager::confirmDeletePair() {
    // TODO: Implement confirmation for deleting a pair
    std::cout << "Confirming delete pair..." << std::endl;
}

void PropulsionManager::confirmDeleteTank() {
    // TODO: Implement confirmation for deleting a pair
    std::cout << "Confirming delete tank..." << std::endl;
}

void PropulsionManager::handleEngineThrusterSelection() {
    // TODO: Confirm only 1 Engine and 1 thruster were selected
    // TODO: Implement logic for handling Engine/Thruster selection
    std::cout << "Handling engine selection..." << std::endl;
    std::cout << "Handling thruster selection..." << std::endl;
}

void PropulsionManager::handleTankSelection() {
    // TODO: Implement logic for handling tank selection
    std::cout << "Handling tank selection..." << std::endl;
}

void PropulsionManager::loadEngineThrusterFromXML() {
    // TODO: Implement loading engine/thruster data from XML
    std::cout << "Loading engine/thruster from XML..." << std::endl;
}

void PropulsionManager::displayEngineThrusterDetails() {
    // TODO: Write logic to display the details of the Engine Thruster pair
    std::cout << "Displaying engine thruster pair details..." << std::endl;
}

void PropulsionManager::displayTankDetails() {
    // TODO: Implement logic to display tank details
    std::cout << "Displaying tank details..." << std::endl;
}

void PropulsionManager::saveEngineThrusterData() {
    // TODO: Implement saving engine/thruster data
    std::cout << "Saving engine/thruster data..." << std::endl;
}

void PropulsionManager::saveTankData() {
    // TODO: Implement saving tank data
    std::cout << "Saving tank data..." << std::endl;
}

/*PropulsionManager::PropulsionManager(Gtk::Window& parent)
    : parentWindow_(nullptr) {} */
/*PropulsionManager::PropulsionManager(Gtk::Window& parent)
    : parentWindow_(&parent) {}*/


void PropulsionManager::initialize(Gtk::Window& parentWindow) {
   parentWindow_ = &parentWindow;
}

/*void PropulsionManager::showTankSetup(Gtk::Window& parentWindow) {
    /*if (!parentWindow_) {
        std::cerr << "Error: Parent window is not initialized!" << std::endl;
        return;
    }

    Tank selectedTank(0, 100.0, 50.0); // Example initialization
    //TankDialog dialogTK(parentWindow_, selectedTank); // Use initialized parentWindow_
    TankDialog dialogTK(*parentWindow_, selectedTank);

    if (dialogTK.run_dialog()) {
        std::cout << "Tank setup completed successfully." << std::endl;
    } else {
        std::cout << "Tank setup was canceled." << std::endl;
    }
}*/

void PropulsionManager::showTankSetup(Gtk::Window& parentWindow, Tank& selectedTank) {
    TankDialog dialog(parentWindow, selectedTank);
    dialog.present();  // Displays the dialog
  // Or correct method for showing the dialog
}


/*void ExampleWindow::someFunction() {
    Tank myTank(1, 100.0, 50.0);  // Initialize the tank
    m_PropManager.showTankSetup(*this, myTank);
}*/
