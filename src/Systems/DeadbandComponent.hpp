#pragma once

#include "ComponentWindowCommon.hpp"

namespace DragDrop {

class DeadbandComponentWindow : public ComponentWindowCommon {
public:
    DeadbandComponentWindow(std::shared_ptr<IComponentCommon> comp, 
                             std::shared_ptr<std::set<std::string>> setOfNames);

private:
    void CreateDeadbandTab();
    void HandleRadioSelection(); // Handles radio button logic for DB-16 and DB-17
    void SaveInfo();             // Saves user inputs
};

};
