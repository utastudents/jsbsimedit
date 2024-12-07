#include "PropulsionManager.hpp"
#include "EngineThrusterDialog.hpp"
#include "PropulsionSubsystem.hpp"
#include "TankDialog.hpp"
#include <iostream>

void PropulsionManager::showEngineThrusterSetup(const std::string& Engine, const std::string& Thruster) { 
    // TODO: Confirm if 1st time setup
    // TODO: Implement engine/thruster setup display
    
    EngineThrusterDialog dialogEng(Engine, Thruster);
    std::cout << "Displaying engine/thruster setup..." << std::endl;
}

void PropulsionManager::showTankSetup() {
    // TODO: Implement tank setup display

    TankDialog dialogTank;
    std::cout << "Displaying tank setup..." << std::endl;
}

int PropulsionManager::createPair(const std::string& Engine, const std::string& Thruster) {
    // TODO: Implement confirmation for creating a pair
    showEngineThrusterSetup(Engine, Thruster);
    std::cout << "Confirming created pair..." << std::endl;
    return 1;
}

void PropulsionManager::createTank() {
    // TODO: Implement confirmation for creating a pair
    std::cout << "Confirming created Tank..." << std::endl;
}

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

