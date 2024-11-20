#ifndef PROPMANAGER_H
#define PROPMANAGER_H

#include <string>
#include <list>

class PropulsionManager {
public:
    void showEngineThrusterSetup();
    void showTankSetup();
    void createPair();
    void createTank();
    void confirmDeletePair();
    void confirmDeleteTank();
    void handleEngineThrusterSelection();
    void handleTankSelection();
    void loadEngineThrusterFromXML();
    void displayEngineThrusterDetails();
    void displayTankDetails();
    void saveEngineThrusterData();
    void saveTankData();

};

#endif // PROPMANAGER_H
