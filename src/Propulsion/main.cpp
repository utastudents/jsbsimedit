#include <iostream>
#include "Engine.hpp"
#include "Tank.hpp"
#include "Thruster.hpp"
#include "EngineThrusterDialog.hpp"
#include "TankDialog.hpp"
#include "MainWindow.hpp"



int main() {
    // Create an instance of Engine
    Engine engine("Main Engine", 0, 1.0f, 2.0f, 45.0f, 1000, 1);
    engine.loadEngineFromXML();
    std::cout << "Engine Power: " << engine.getPower() << ", Augmented: " << engine.getAugmented() << std::endl;

    // Create an instance of Thruster
    Thruster thruster("Side Thruster", 1, 3.0f, 4.0f, 90.0f, 500.0, "Newtons");
    thruster.loadThrusterFromXML();
    std::cout << "Thruster Thrust: " << thruster.getThrust() << " " << thruster.getThrustUnit() << std::endl;

    // Create dialogs
    EngineThrusterDialog engineThrusterDialog;
    engineThrusterDialog.onConfirm();
    engineThrusterDialog.onCancel();

    TankDialog tankDialog;
    tankDialog.onConfirm();
    tankDialog.onCancel();

    // Create MainWindow and simulate actions
    MainWindow mainWindow;
    mainWindow.showEngineThrusterSetup();
    mainWindow.showTankSetup();
    mainWindow.confirmDeletePair();
    mainWindow.handleTankSelection();
    mainWindow.loadEngineThrusterFromXML();
    mainWindow.displayTankDetails();
    mainWindow.saveEngineThrusterData();
    mainWindow.saveTankData();

    return 0;
}
