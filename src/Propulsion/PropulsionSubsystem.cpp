#include <iostream>
#include <vector> // For buttonNames
#include <map>  // For buttonMap
#include <utility> // For std::pair
#include "PropulsionSubsystem.hpp"
#include "PropulsionManager.hpp"

PropulsionSubsystem::PropulsionSubsystem() {
    m_Name = "Propulsion";
    std::cout << "In PropulsionSubsystem contructor" << std::endl; 
}

void PropulsionSubsystem::Create() {
  std::cout << "in PropulsionSubsystem::Create" << std::endl;


  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  std::map<std::pair<int, int>, Gtk::ToggleButton*> buttonMap; 

  // Seperated line of code for readability 
  std::vector<std::string> buttonNames = {
    // Engine Thruster Button Names
    "Create Engine/Thruster Pair", "Engine/Thruster Pair Details", "Delete Engine/Thruster Pair", 
    // Tank Button Names
    "Create Tank", "Tank Details", "Delete Tank"};

  int nameIndex = 0;
  
  // Define the unique actions for each button in lambdas
  std::vector<std::function<void()>> buttonActions = {
    [this]() { m_PropManager.showEngineThrusterSetup(); },
    [this]() { m_PropManager.showEngineThrusterSetup(); },
    [this]() { m_PropManager.confirmDeletePair(); },
    [this]() { m_PropManager.showTankSetup(); },
    [this]() { m_PropManager.showTankSetup(); },
    [this]() { m_PropManager.confirmDeleteTank(); }
  };

  // i is length # j is height #
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      if (nameIndex < buttonNames.size()) {
        // Create each button with a unique name
        auto pButton = Gtk::make_managed<Gtk::ToggleButton>(buttonNames[nameIndex]);
        m_Grid.attach(*pButton, i, j);  // Place in grid (i, j) to fill bottom-right

        // Store Buttons in map for accessability 
        buttonMap[{i, j}] = pButton;
                
        // Connect each button's signal to its specific lambda function
        pButton->signal_clicked().connect(buttonActions[nameIndex]);


        // Move to the next name
        nameIndex++;
      } 
    }
  }
}

