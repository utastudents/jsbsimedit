#ifndef PROPMANAGER_H
#define PROPMANAGER_H

#include <string>
#include <list>
#include <gtkmm.h> 
#include "Tank.hpp"
#include "PropulsionSubsystem.hpp"

class PropulsionManager {
public:

    void showEngineThrusterSetup(const std::string& Engine, const std::string& Thruster); 
    void showTankSetup();
    int createPair(const std::string& Engine, const std::string& Thruster);
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
