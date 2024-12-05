#pragma once

#include "SwitchComponent.hpp"
#include "ComponentWindowCommon.hpp"

namespace DragDrop{

class SwitchComponentWindow : public ComponentWindowCommon
{
    public:
        SwitchComponentWindow(std::shared_ptr<IComponentCommon> comp, 
            std::shared_ptr<std::set<std::string>> setOfNames);
    private:
        void Switch();
        void SaveInfo(); //xml must store info here to show options
};

};