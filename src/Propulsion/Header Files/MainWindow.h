#pragma once
#include <string>
#include <list>

class MainWindow {
public:
    void showEngineThrusterSetup();
    void showTankSetup();
    void confirmDeletePair();
    void handleTankSelection();
    void loadEngineThrusterFromXML();
    void displayTankDetails();
    void saveEngineThrusterData();
    void saveTankData();

};
