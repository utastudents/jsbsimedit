#pragma once

#include "ComponentWindowCommon.hpp"

namespace DragDrop {

class FilterComponentWindow : public ComponentWindowCommon {
public:
    FilterComponentWindow(std::shared_ptr<IComponentCommon> comp, 
                          std::shared_ptr<std::set<std::string>> setOfNames);

private:
    bool checkboxState = false;  // Tracks the state of FC-21 checkbox

    void CreateFilterTab();
    void HandleRadioSelection(); // Handles radio button logic for FC-16 and FC-17
    void SaveInfo();             // Saves user inputs
};

};