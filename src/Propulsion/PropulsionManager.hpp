#ifndef PROPMANAGER_H
#define PROPMANAGER_H

#include <string>
#include <list>
#include <gtkmm.h> 
#include "Tank.hpp"

class PropulsionManager {
public:
    //PropulsionManager() : parentWindow_(nullptr) {}
    //explicit PropulsionManager(Gtk::Window& parent) : parentWindow_(parent) {}
    explicit PropulsionManager(Gtk::Window& parent) : parentWindow_(&parent) {}

    //void initialize(Gtk::Window& parentWindow); 
    void initialize(Gtk::Window& parentWindow);// { parentWindow_ = &parentWindow; }
    void showTankSetup(Gtk::Window& parentWindow, Tank& selectedTank);

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
    Tank selectedTank;
private:
    Gtk::Window* parentWindow_; 

};

#endif // PROPMANAGER_H
