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

  // i is length # j is height #
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      if (nameIndex < buttonNames.size()) {
        // Create each button with a unique name
        auto pButton = Gtk::make_managed<Gtk::ToggleButton>(buttonNames[nameIndex]);
        m_Grid.attach(*pButton, i, j);  // Place in grid (i, j) to fill bottom-right

        // Store Buttons in map for accessability 
        buttonMap[{i, j}] = pButton;
                
        // Assign specific actions based on button position
        // Engine/Thruster specific buttons
        if (i == 0 && j == 0) { // "Create Engine/Thruster Pair"
          std::cout << "Create Engine/Thruster Pair" << std::endl;
        } else if (i == 0 && j == 1) { // "Engine/Thruster Pair Details"
          std::cout << "Engine/Thruster Pair Details" << std::endl;
        }else if (i == 0 && j == 2) { // "Delete Engine/Thruster Pair"
          std::cout << "Delete Engine/Thruster Pair" << std::endl;
        }

        // Tank specific buttons
        if (i == 1 && j == 0) { // "Create Tank"
          std::cout << "Create Tank" << std::endl;
        } else if (i == 1 && j == 1) { // "Tank Details"
          std::cout << "Tank Details" << std::endl;
        } else if (i == 1 && j == 2) { // "Delete Tank"
          std::cout << "Delete Tank" << std::endl;
        }

        // Move to the next name
        nameIndex++;
      } 
    }
  }
}
