#pragma once

#include "SwitchComponent.hpp"
#include "ComponentWindowCommon.hpp"

namespace DragDrop {

class SwitchComponentWindow : public ComponentWindowCommon {
public:
    SwitchComponentWindow(std::shared_ptr<IComponentCommon> comp, 
                          std::shared_ptr<std::set<std::string>> setOfNames);

private:
    void SwitchBasic();
    void SwitchInput();
    void SwitchOutput();
    void SaveInfo(); // Save XML configurations from the UI
};

}