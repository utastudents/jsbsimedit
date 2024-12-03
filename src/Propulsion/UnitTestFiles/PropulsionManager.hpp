#ifndef PROPMANAGER_H
#define PROPMANAGER_H

#include <string>
#include <list>
#include <gtkmm.h> 
#include "Tank.hpp"
#include "PropulsionSubsystem.hpp"

class PropulsionManager {
public:

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
    void showEngineThrusterSetup(); 
    void showTankSetup();

};

#endif // PROPMANAGER_H
